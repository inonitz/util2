#include <util2/C/random.h>
#include <util2/C/macro.h>
#include <util2/C/mt19937ii.h>


static void initRNGOnce();

/* Global State */
static uint8_t gs_initEngine = 0;




u8  UTIL2_API random8u()  { return random32u() & UINT8_MAX;  }
u16 UTIL2_API random16u() { return random32u() & UINT16_MAX; }
u32 UTIL2_API random32u()
{
    initRNGOnce();
    return util2_generate32BitUnsignedInt();
}

u64 UTIL2_API random64u()
{
    initRNGOnce();
    return util2_generate32BitUnsignedInt() + util2_generate32BitUnsignedInt();
}

i8  UTIL2_API random8i()  { return (i8)(random32i()  & UINT8_MAX);  }
i16 UTIL2_API random16i() { return (i16)(random32i() & UINT16_MAX); }
i32 UTIL2_API random32i()
{
    initRNGOnce();
    const uint32_t k_highestBit = 0x80000000; /* 1 << 31 */
    uint32_t out   = 0;
    int32_t  res   = 0;
    uint8_t  isNeg = 0;

    out   = util2_generate32BitUnsignedInt();
    isNeg = out & k_highestBit;
    res   = (int32_t)(out >> 1);

    return isNeg ? -res : res;
}

i64 UTIL2_API random64i()
{
    initRNGOnce();
    const uint64_t k_highestBit = 0x8000000000000000; /* 1 << 63 */
    uint64_t out   = 0;
    int64_t  res   = 0;
    uint8_t  isNeg = 0;

    out   = random64u();
    isNeg = out & k_highestBit;
    res   = (int64_t)(out >> 1);

    return isNeg ? -res : res;
}




void initRNGOnce()
{
    if(likely(gs_initEngine)) {
        return;
    }


    util2_initializeMersenneTwister19937Ver2_Default();
    gs_initEngine = 1;
    return;
}
