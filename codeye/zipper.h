#ifndef zipperH
#define zipperH

/* Based on Public Domain code */

#include <stdint.h>

#define ZIPR_MAX_OFF       (1 << 15)
#define ZIPR_WIN_SIZ       ZIPR_MAX_OFF
#define ZIPR_WIN_MSK       (ZIPR_WIN_SIZ-1)

#define ZIPR_MIN_MATCH     4
#define ZIPR_MAX_MATCH     258

#define ZIPR_HASH_BITS     19
#define ZIPR_HASH_SIZ      (1 << ZIPR_HASH_BITS)
#define ZIPR_HASH_MSK      (ZIPR_HASH_SIZ-1)
#define ZIPR_NIL           (-1)

#define ZIPR_LVL_MIN       0
#define ZIPR_LVL_DEF       5
#define ZIPR_LVL_MAX       8

struct zipr {
    int bits, cnt;
    int tbl[ZIPR_HASH_SIZ];
    int prv[ZIPR_WIN_SIZ];
};

struct unzipr {
    int bits, bitcnt;
    unsigned lits[288];
    unsigned dsts[32];
    unsigned lens[19];
    int tlit, tdist, tlen;
};

int zipr_bound(int in_len);
int zipr_deflate(struct zipr *s, uint8_t *out, const uint8_t *in, int in_len, int lvl);
int zipr_inflate(uint8_t *out, const uint8_t *in, int size);

#endif
 