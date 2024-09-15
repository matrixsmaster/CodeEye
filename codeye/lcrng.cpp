//---------------------------------------------------------------------------
#include <stdlib.h>
#include <string.h>
#pragma hdrstop

#include "lcrng.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
CLCRNG::CLCRNG()
{
    seed = time(NULL);
    log = new TStringList(); //FIXME: debug only!
}
//---------------------------------------------------------------------------
CLCRNG::CLCRNG(uint32_t nseed)
{
    setSeed(nseed);
}
//---------------------------------------------------------------------------
CLCRNG::~CLCRNG()
{
    //FIXME: debug only!
    log->SaveToFile("lcrng.txt");
    delete log;
}
//---------------------------------------------------------------------------
void CLCRNG::setSeed(uint32_t nseed)
{
    seed = nseed;
    next = seed;
    Run();
}
//---------------------------------------------------------------------------
void CLCRNG::setSeed(const char* seedstr)
{
    int len = strlen(seedstr);
    uint32_t nsd = 0, buf = 0;

    for (int i = 0; i < len; i++) {
        buf <<= 8;
        buf |= seedstr[i];
        if ((i & 3) == 3) {
            nsd += buf;
            buf = 0;
        }
    }
    nsd += buf;

    setSeed(nsd);
}
//---------------------------------------------------------------------------
void CLCRNG::Run()
{
    next = (LCRNG_A * next + LCRNG_C) % LCRNG_M;
    log->Add(IntToHex((int)next,8));
}
//---------------------------------------------------------------------------
uint32_t CLCRNG::getDWord()
{
    Run();
    return next;
}
//---------------------------------------------------------------------------
int CLCRNG::getPosInt()
{
    Run();
    int r = next & 0x7FFFFFFFUL;
    return r;
}
//---------------------------------------------------------------------------
