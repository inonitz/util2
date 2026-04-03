#ifndef __UTIL2_C_DEFINITION_ENVIRONMENT_VARIABLES__
#define __UTIL2_C_DEFINITION_ENVIRONMENT_VARIABLES__
#include "util2_extern.h"
#include "util2_api.h"
#include "base_type.h"


UTIL2_EXTERNC_DECL_BEGIN


UTIL2_API i32 util2_putenv(const char* str);
UTIL2_API i32 util2_setenv(const char* name, const char* val, bool_t replace_if_exists);


UTIL2_EXTERNC_DECL_END


#endif /* __UTIL2_C_DEFINITION_ENVIRONMENT_VARIABLES__ */
