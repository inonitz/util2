#ifndef __UTIl2_PUBLIC_DOMAIN_MERSENNE_TWISTER_ENGINE_VERSION2_2014_11_10_DEFINITION_HEADER__
#define __UTIl2_PUBLIC_DOMAIN_MERSENNE_TWISTER_ENGINE_VERSION2_2014_11_10_DEFINITION_HEADER__
#include "util2_extern.h"
#include "util2_api.h"
#include "util2/C/base_type.h"


UTIL2_EXTERNC_DECL_BEGIN


void   UTIL2_API util2_initializeMersenneTwister19937Ver2_Default();
void   UTIL2_API util2_initializeMersenneTwister19937Ver2_RandomKeyBuffer(
    u32 const* keyBuf, 
    i32        keyBufLength
);
u32    UTIL2_API util2_generate31BitUnsignedInt();
u32    UTIL2_API util2_generate32BitUnsignedInt();
double UTIL2_API util2_generateRealOnClosedInterval(void);
double UTIL2_API util2_generateRealOnHalfClosedInterval(void);
double UTIL2_API util2_generateRealOnOpenInterval(void);
double UTIL2_API util2_generateRealOnHalfClosedInterval53Bits(void);


UTIL2_EXTERNC_DECL_END


#endif /* __UTIl2_PUBLIC_DOMAIN_MERSENNE_TWISTER_ENGINE_VERSION2_2014_11_10_DEFINITION_HEADER__ */
