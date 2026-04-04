#include <util2/C/random.h>
#include <util2/C/macro.h>
#include <util2/C/mt19937ii.h>
#include <stdlib.h>
#include <time.h>


static void initRNGOnceRand();


/* Global State */
static uint8_t gs_initEngine = 0;


void randomInitDefault()
{
    initRNGOnceRand();
    return;
}

void randomInitFixedSeed()
{
    if(likely(gs_initEngine)) {
        return;
    }
    util2_initializeMersenneTwister19937Ver2_FixedDefault();
    gs_initEngine = 1;
    return;
}

void randomGetSeed(
    u32* seedBufferAddress, 
    u8   seedBufferAddressLength
) {
    if(!gs_initEngine || seedBufferAddressLength < 8) {
        return;
    }
    util2_getMersenneTwister19937Ver2_KeyBuffer(
        (util2_mt19937ii_keyBuffer_t*)seedBufferAddress
    );
    return;
}



u8  random8u()  { return random32u() & UINT8_MAX;  }
u16 random16u() { return random32u() & UINT16_MAX; }
u32 random32u()
{
    initRNGOnceRand();
    return util2_generate32BitUnsignedInt();
}

u64 random64u()
{
    initRNGOnceRand();
    return util2_generate32BitUnsignedInt() + util2_generate32BitUnsignedInt();
}

i8  random8i()  { return (i8)(random32i()  & UINT8_MAX);  }
i16 random16i() { return (i16)(random32i() & UINT16_MAX); }
i32 random32i()
{
    initRNGOnceRand();
    const uint32_t k_highestBit = 0x80000000; /* 1 << 31 */
    uint32_t out   = 0;
    int32_t  res   = 0;
    uint8_t  isNeg = 0;

    out   = util2_generate32BitUnsignedInt();
    isNeg = out & k_highestBit;

    out &= ~k_highestBit; /* Reset the bit we just used to not introduce bias */
    res  = (int32_t)out;
    res *= (isNeg ? -1 : 1);

    return res;
}

i64 random64i()
{
    initRNGOnceRand();
    const uint64_t k_highestBit = 0x8000000000000000; /* 1 << 63 */
    uint64_t out   = 0;
    int64_t  res   = 0;
    uint8_t  isNeg = 0;

    out   = random64u();
    isNeg = out & k_highestBit;
    res   = (int64_t)(out >> 1);

    return isNeg ? -res : res;
}

/* Normalized To Range [0, 1] */
f32 random32f()
{
    initRNGOnceRand();
    return (f32)util2_generateRealOnClosedInterval();
}

/* Normalized To Range [0, 1] */
f64 random64f()
{
    initRNGOnceRand();
    return util2_generateRealOnClosedInterval();
}



/*
    [NOTE]:
    I've definitely considered using __attribute__((constructor)) and its friends
    instead of this function call, But it might not work on some platforms ;
    It requires extensive testing on my end, and even then,
    it might just break on an SDK update (Looking at you MSVC!).
    
    For More info regarding implementation details and edge cases:
    1. https://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
    2. https://sillycross.github.io/2022/10/02/2022-10-02/
*/
void initRNGOnceRand()
{
    if(likely(gs_initEngine)) {
        return;
    }

    
    util2_mt19937ii_keyBuffer_t keyBuffer = {};
    srand(time(NULL));
    for(uint8_t i = 0; i < __carraysize(keyBuffer); ++i) {
        keyBuffer[i] = rand();
    }
    util2_initializeMersenneTwister19937Ver2_ExistingKeyBuffer(&keyBuffer);
    gs_initEngine = 1;
    return;
}
