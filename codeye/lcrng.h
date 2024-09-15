//---------------------------------------------------------------------------
#ifndef lcrngH
#define lcrngH

#include <stdint.h>
#include <vcl.h> // FIXME: debug only

#define LCRNG_A 16807UL
#define LCRNG_C 0
#define LCRNG_M 2147483647UL

//---------------------------------------------------------------------------
class CLCRNG
{
public:
    CLCRNG();
    CLCRNG(uint32_t nseed);
    virtual ~CLCRNG();

    void setSeed(uint32_t nseed);
    void setSeed(const char* seedstr);

    uint32_t getDWord();
    //int getInt();
    int getPosInt();
    //int getRanged(int range);
    //float getFloat();

private:
    uint32_t seed, next;
    TStrings* log; //FIXME: debug only!

    void Run();
};
//---------------------------------------------------------------------------
#endif
