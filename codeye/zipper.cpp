#include <stdlib.h>
#include <string.h>
#pragma hdrstop

#include "zipper.h"

#pragma package(smart_init)

static const uint8_t zipr_mirror[256] = {
    #define R2(n) n, n + 128, n + 64, n + 192
    #define R4(n) R2(n), R2(n + 32), R2(n + 16), R2(n + 48)
    #define R6(n) R4(n), R4(n +  8), R4(n +  4), R4(n + 12)
    R6(0), R6(2), R6(1), R6(3),
};

static int zipr_npow2(int n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    return ++n;
}

static int zipr_ilog2(int n)
{
    #define lt(n) n,n,n,n, n,n,n,n, n,n,n,n ,n,n,n,n
    static const char tbl[256] = {-1,0,1,1,2,2,2,2,3,3,3,3,
        3,3,3,3,lt(4),lt(5),lt(5),lt(6),lt(6),lt(6),lt(6),
        lt(7),lt(7),lt(7),lt(7),lt(7),lt(7),lt(7),lt(7)
    };
    int tt, t;
    if ((tt = (n >> 16))) return (t = (tt >> 8)) ? 24+tbl[t]: 16+tbl[tt];
    return (t = (n >> 8)) ? 8+tbl[t]: tbl[n];
    #undef lt
}

static unsigned zipr_uload32(const void *p)
{
    /* hopefully will be optimized to an unaligned read */
    unsigned int n = 0;
    memcpy(&n, p, sizeof(n));
    return n;
}

static unsigned zipr_hash32(const void *p)
{
    unsigned n = zipr_uload32(p);
    return (n*0x9E377989)>>(32-ZIPR_HASH_BITS);
}

static uint8_t* zipr_put(uint8_t *dst, struct zipr *s, int code, int bitcnt)
{
    s->bits |= (code << s->cnt);
    s->cnt += bitcnt;
    while (s->cnt >= 8) {
        *dst++ = (uint8_t)(s->bits & 0xFF);
        s->bits >>= 8;
        s->cnt -= 8;
    }
    return dst;
}

static uint8_t* zipr_match(uint8_t *dst, struct zipr *s, int dist, int len)
{
    static const short lxmin[] = {0,11,19,35,67,131};
    static const short dxmax[] = {0,6,12,24,48,96,192,384,768,1536,3072,6144,12288,24576};
    static const short lmin[] = {11,13,15,17,19,23,27,31,35,43,51,59,67,83,99,115,131,163,195,227};
    static const short dmin[] = {1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,257,
                                 385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577};

    /* length encoding */
    int lc = len;
    int lx = zipr_ilog2(len - 3) - 2;
    if (!(lx = (lx < 0) ? 0: lx)) lc += 254;
    else if (len >= 258) lx = 0, lc = 285;
    else lc = ((lx-1) << 2) + 265 + ((len - lxmin[lx]) >> lx);

    if (lc <= 279)
        dst = zipr_put(dst, s, zipr_mirror[(lc - 256) << 1], 7);
    else dst = zipr_put(dst, s, zipr_mirror[0xc0 - 280 + lc], 8);
    if (lx) dst = zipr_put(dst, s, len - lmin[lc - 265], lx);

    /* distance encoding */
    {int dc = dist - 1;
    int dx = zipr_ilog2(zipr_npow2(dist) >> 2);
    if ((dx = (dx < 0) ? 0: dx))
        dc = ((dx + 1) << 1) + (dist > dxmax[dx]);
    dst = zipr_put(dst, s, zipr_mirror[dc << 3], 5);
    if (dx) dst = zipr_put(dst, s, dist - dmin[dc], dx);}
    return dst;
}

static uint8_t* zipr_lit(uint8_t *dst, struct zipr *s, int c)
{
    if (c <= 143) return zipr_put(dst, s, zipr_mirror[0x30+c], 8);
    return zipr_put(dst, s, 1 + 2 * zipr_mirror[0x90 - 144 + c], 9);
}

extern int zipr_deflate(struct zipr *s, uint8_t *out, const uint8_t *in, int in_len, int lvl)
{
    int p = 0;
    int max_chain = (lvl < 8) ? (1<<(lvl+1)): (1<<13);
    uint8_t *q = out;

    s->bits = s->cnt = 0;
    for (p = 0; p < ZIPR_HASH_SIZ; ++p)
        s->tbl[p] = ZIPR_NIL;

    p = 0;
    q = zipr_put(q, s, 0x01, 1); /* block */
    q = zipr_put(q, s, 0x01, 2); /* static huffman */
    while (p < in_len) {
        int run, best_len = 0, dist = 0;
        int max_match = ((in_len-p)>ZIPR_MAX_MATCH) ? ZIPR_MAX_MATCH:(in_len-p);
        if (max_match > ZIPR_MIN_MATCH) {
            int limit = ((p-ZIPR_WIN_SIZ)<ZIPR_NIL)?ZIPR_NIL:(p-ZIPR_WIN_SIZ);
            int chain_len = max_chain;
            int i = s->tbl[zipr_hash32(&in[p])];
            while (i > limit) {
                if (in[i+best_len] == in[p+best_len] &&
                    (zipr_uload32(&in[i]) == zipr_uload32(&in[p]))){
                    int n = ZIPR_MIN_MATCH;
                    while (n < max_match && in[i+n] == in[p+n]) n++;
                    if (n > best_len) {
                        best_len = n;
                        dist = p - i;
                        if (n == max_match)
                            break;
                    }
                }
                if (!(--chain_len)) break;
                i = s->prv[i&ZIPR_WIN_MSK];
            }
        }
        if (lvl >= 5 && best_len >= ZIPR_MIN_MATCH && best_len < max_match){
            const int x = p + 1;
            int tar_len = best_len + 1;
            int limit = ((x-ZIPR_WIN_SIZ)<ZIPR_NIL)?ZIPR_NIL:(x-ZIPR_WIN_SIZ);
            int chain_len = max_chain;
            int i = s->tbl[zipr_hash32(&in[p])];
            while (i > limit) {
                if (in[i+best_len] == in[x+best_len] &&
                    (zipr_uload32(&in[i]) == zipr_uload32(&in[x]))){
                    int n = ZIPR_MIN_MATCH;
                    while (n < tar_len && in[i+n] == in[x+n]) n++;
                    if (n == tar_len) {
                        best_len = 0;
                        break;
                    }
                }
                if (!(--chain_len)) break;
                i = s->prv[i&ZIPR_WIN_MSK];
            }
        }
        if (best_len >= ZIPR_MIN_MATCH) {
            q = zipr_match(q, s, dist, best_len);
            run = best_len;
        } else {
            q = zipr_lit(q, s, in[p]);
            run = 1;
        }
        while (run-- != 0) {
            unsigned h = zipr_hash32(&in[p]);
            s->prv[p&ZIPR_WIN_MSK] = s->tbl[h];
            s->tbl[h] = p++;
        }
    }
    /* zlib partial flush */
    q = zipr_put(q, s, 0, 7);
    q = zipr_put(q, s, 2, 10);
    q = zipr_put(q, s, 2, 3);
    return (q - out);
}

int zipr_bound(int len)
{
    int a = 128 + (len * 110) / 100;
    int b = 128 + len + ((len / (31 * 1024)) + 1) * 5;
    return (a > b) ? a : b;
}

static int zipr_get(const uint8_t **src, const uint8_t *end, struct unzipr *s, int n)
{
    const uint8_t *in = *src;
    int v = s->bits & ((1 << n)-1);
    s->bits >>= n;
    s->bitcnt = s->bitcnt - n;
    s->bitcnt = s->bitcnt < 0 ? 0 : s->bitcnt;
    while (s->bitcnt < 16 && in < end) {
        s->bits |= (*in++) << s->bitcnt;
        s->bitcnt += 8;
    }
    *src = in;
    return v;
}

static int zipr_build(unsigned *tree, uint8_t *lens, int symcnt)
{
    int n, cnt[16], first[16], codes[16];
    memset(cnt, 0, sizeof(cnt));
    cnt[0] = first[0] = codes[0] = 0;
    for (n = 0; n < symcnt; ++n) cnt[lens[n]]++;
    for (n = 1; n <= 15; n++) {
        codes[n] = (codes[n-1] + cnt[n-1]) << 1;
        first[n] = first[n-1] + cnt[n-1];
    }
    for (n = 0; n < symcnt; n++) {
        int slot, code, len = lens[n];
        if (!len) continue;
        code = codes[len]++;
        slot = first[len]++;
        tree[slot] = (unsigned)((code << (32-len)) | (n << 4) | len);
    }
    return first[15];
}

static int zipr_decode(const uint8_t **in, const uint8_t *end, struct unzipr *s, unsigned *tree, int max)
{
    /* bsearch next prefix code */
    #define zipr_rev16(n) ((zipr_mirror[(n)&0xff] << 8) | zipr_mirror[((n)>>8)&0xff])
    unsigned key, lo = 0, hi = (unsigned)max;
    unsigned search = (unsigned)(zipr_rev16(s->bits) << 16) | 0xffff;
    while (lo < hi) {
        unsigned guess = (lo + hi) / 2;
        if (search < tree[guess]) hi = guess;
        else lo = guess + 1;
    }
    /* pull out and check key */
    key = tree[lo-1];
    zipr_get(in, end, s, key & 0x0f);
    return (key >> 4) & 0x0fff;
}

int zipr_inflate(uint8_t *out, const uint8_t *in, int size)
{
    static const char order[] = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
    static const short dbase[30+2] = {1,2,3,4,5,7,9,13,17,25,33,49,65,97,129,193,
                                      257,385,513,769,1025,1537,2049,3073,4097,6145,8193,12289,16385,24577};
    static const uint8_t dbits[30+2] = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,
                                              10,10,11,11,12,12,13,13,0,0};
    static const short lbase[29+2] = {3,4,5,6,7,8,9,10,11,13,15,17,19,23,27,31,35,
                                      43,51,59,67,83,99,115,131,163,195,227,258,0,0};
    static const uint8_t lbits[29+2] = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,
                                              4,4,4,5,5,5,5,0,0,0};

    const uint8_t *e = in + size, *o = out;
    enum zipr_states {hdr,stored,fixed,dyn,blk};
    enum zipr_states state = hdr;
    struct unzipr s;
    int last = 0;

    memset(&s, 0, sizeof(s));
    zipr_get(&in,e,&s,0); /* buffer input */
    while (in < e || s.bitcnt) {
        switch (state) {
        case hdr: {
            int type = 0; /* block header */
            last = zipr_get(&in,e,&s,1);
            type = zipr_get(&in,e,&s,2);

            switch (type) {default: return (int)(out-o);
            case 0x00: state = stored; break;
            case 0x01: state = fixed; break;
            case 0x02: state = dyn; break;}
        } break;
        case stored: {
            int len, nlen; /* uncompressed block */
            zipr_get(&in,e,&s,s.bitcnt & 7);
            len = zipr_get(&in,e,&s,16);
            nlen = zipr_get(&in,e,&s,16);
            in -= 2; s.bitcnt = 0;

            if (len > (e-in) || !len) return (int)(out-o);
            memcpy(out, in, (size_t)len);
            in += len, out += len;
            state = hdr;
        } break;
        case fixed: {
            /* fixed huffman codes */
            int n; uint8_t lens[288+32];
            for (n = 0; n <= 143; n++) lens[n] = 8;
            for (n = 144; n <= 255; n++) lens[n] = 9;
            for (n = 256; n <= 279; n++) lens[n] = 7;
            for (n = 280; n <= 287; n++) lens[n] = 8;
            for (n = 0; n < 32; n++) lens[288+n] = 5;

            /* build trees */
            s.tlit  = zipr_build(s.lits, lens, 288);
            s.tdist = zipr_build(s.dsts, lens + 288, 32);
            state = blk;
        } break;
        case dyn: {
            /* dynamic huffman codes */
            int n, i, nlit, ndist, nlen;
            uint8_t nlens[19] = {0}, lens[288+32];
            nlit = 257 + zipr_get(&in,e,&s,5);
            ndist = 1 + zipr_get(&in,e,&s,5);
            nlen = 4 + zipr_get(&in,e,&s,4);
            for (n = 0; n < nlen; n++)
                nlens[order[n]] = (uint8_t)zipr_get(&in,e,&s,3);
            s.tlen = zipr_build(s.lens, nlens, 19);

            /* decode code lengths */
            for (n = 0; n < nlit + ndist;) {
                int sym = zipr_decode(&in, e, &s, s.lens, s.tlen);
                switch (sym) {default: lens[n++] = (uint8_t)sym; break;
                case 16: for (i=3+zipr_get(&in,e,&s,2);i;i--,n++) lens[n]=lens[n-1]; break;
                case 17: for (i=3+zipr_get(&in,e,&s,3);i;i--,n++) lens[n]=0; break;
                case 18: for (i=11+zipr_get(&in,e,&s,7);i;i--,n++) lens[n]=0; break;}
            }
            /* build lit/dist trees */
            s.tlit  = zipr_build(s.lits, lens, nlit);
            s.tdist = zipr_build(s.dsts, lens+nlit, ndist);
            state = blk;
        } break;
        case blk: {
            /* decompress block */
            int sym = zipr_decode(&in, e, &s, s.lits, s.tlit);
            if (sym > 256) {sym -= 257; /* match symbol */
                {int len = zipr_get(&in, e, &s, lbits[sym]) + lbase[sym];
                int dsym = zipr_decode(&in, e, &s, s.dsts, s.tdist);
                int offs = zipr_get(&in, e, &s, dbits[dsym]) + dbase[dsym];
                if (offs > (int)(out-o)) return (int)(out-o);
                while (len--) *out = *(out-offs), out++;}
            } else if (sym == 256) {
                if (last) return (int)(out-o);
                state = hdr;
            } else *out++ = (uint8_t)sym;
        } break;
        }
    }
    return (out-o);
}

