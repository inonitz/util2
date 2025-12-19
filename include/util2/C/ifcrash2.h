#ifndef __UTIL2_C_DEFINITION_IFCRASH2_MACRO__
#define __UTIL2_C_DEFINITION_IFCRASH2_MACRO__
// #define UTIL2_IFCRASH2_DISABLE 1
#define UTIL2_IFCRASH2_KEEP_RELEASE           1
#define UTIL2_IFCRASH2_INCLUDE_NEWLINE_AT_END 1
// #define UTIL2_IFCRASH2_LOG_TO_FILE 1


#ifndef UTIL2_IFCRASH2_DISABLE
#	define UTIL2_IFCRASH2_DISABLE 0
#endif
#ifndef UTIL2_IFCRASH2_KEEP_RELEASE
#	define UTIL2_IFCRASH2_KEEP_RELEASE 0
#endif
#ifndef UTIL2_IFCRASH2_INCLUDE_NEWLINE_AT_END
#	define UTIL2_IFCRASH2_INCLUDE_NEWLINE_AT_END 0
#endif
#ifndef UTIL2_IFCRASH2_LOG_TO_FILE
#	define UTIL2_IFCRASH2_LOG_TO_FILE 0
#endif
#if !(UTIL2_IFCRASH2_DISABLE) & (defined(_DEBUG) | defined(DEBUG) | (UTIL2_IFCRASH2_KEEP_RELEASE))
#	undef UTIL2_IFCRASH2_DEFINE_IMPLEMENTATION
#	define UTIL2_IFCRASH2_DEFINE_IMPLEMENTATION 1
#endif


#if UTIL2_IFCRASH2_DEFINE_IMPLEMENTATION == 1
#	include "util2/C/util2_api.h"
#	include "util2/C/util2_extern.h"
#   include "util2/C/macro.h"
#   include "util2/C/base_type.h"


#if defined(ifcrash)
#	error "ifcrash should not be defined before this point. You must have mixed ifcrash.hpp & ifcrash2.h"
#endif
#if defined(ifcrashstr)
#	error "ifcrashstr should not be defined before this point. You must have mixed ifcrash.hpp & ifcrash2.h"
#endif
#if defined(ifcrashfmt)
#	error "ifcrashfmt should not be defined before this point. You must have mixed ifcrash.hpp & ifcrash2.h"
#endif
#if defined(ifcrashdo)
#	error "ifcrashdo should not be defined before this point. You must have mixed ifcrash.hpp & ifcrash2.h"
#endif


UTIL2_API UTIL2_EXTERNC void util2_ifcrash2(
    const char*  ifcrash_type_str,
    const char*  file_macro,
    u64          line_macro,
    bool_t       condition,
    bool_t       formatempty,
    const char*  formatstr,
    ...
);


#   define ifcrash(condition) 			    util2_ifcrash2("",     __FILE__, __LINE__, (condition), BOOL_TRUE,  "",  "")
#   define ifcrashstr(condition, str) 	    util2_ifcrash2("STR",  __FILE__, __LINE__, (condition), BOOL_TRUE,  str, "")
#   define ifcrashfmt(condition, str, ...)  util2_ifcrash2("FMT",  __FILE__, __LINE__, (condition), BOOL_FALSE, str, __VA_ARGS__)
#   define ifcrashdo(condition, ...) \
        if((condition)) { \
            { __VA_ARGS__ } \
            util2_ifcrash2("CODE", __FILE__, __LINE__, (BOOL_TRUE), BOOL_FALSE, "",  ""); \
        } \


#endif /* UTIL2_IFCRASH2_DISABLE */


#endif /* __UTIL2_C_DEFINITION_IFCRASH2_MACRO__ */