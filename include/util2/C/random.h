#ifndef __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_MET19937_II__
#define __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_MET19937_II__
#include "util2_extern.h"
#include "util2_api.h"
#include "base_type.h"


UTIL2_EXTERNC_DECL_BEGIN

void UTIL2_API randomInitDefault(void);
void UTIL2_API randomInitFixedSeed(void);
void UTIL2_API randomGetSeed(
    u32* seedBufferAddress, 
    u8   seedBufferAddressLength
);

u8  UTIL2_API random8u(void);
u16 UTIL2_API random16u(void);
u32 UTIL2_API random32u(void);
u64 UTIL2_API random64u(void);
i8  UTIL2_API random8i(void);
i16 UTIL2_API random16i(void);
i32 UTIL2_API random32i(void);
i64 UTIL2_API random64i(void);
f32 UTIL2_API random32f(void); /* Normalized To Range [0, 1] */
f64 UTIL2_API random64f(void); /* Normalized To Range [0, 1] */

UTIL2_EXTERNC_DECL_END


#endif /* __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_MET19937_II__ */
