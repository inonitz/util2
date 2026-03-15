#ifndef __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_MEMT19937_II__
#define __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_MEMT19937_II__
#include "util2_extern.h"
#include "util2_api.h"
#include "base_type.h"


UTIL2_EXTERNC_DECL_BEGIN

u8  UTIL2_API random8u();
u16 UTIL2_API random16u();
u32 UTIL2_API random32u();
u64 UTIL2_API random64u();
i8  UTIL2_API random8i();
i16 UTIL2_API random16i();
i32 UTIL2_API random32i();
i64 UTIL2_API random64i();
f32 UTIL2_API random32f(); /* Normalized To Range [0, 1] */
f64 UTIL2_API random64f(); /* Normalized To Range [0, 1] */

UTIL2_EXTERNC_DECL_END


#endif /* __UTIL2_RANDOM_NUMBER_GENERATOR_DEFINITION_WELL512__ */