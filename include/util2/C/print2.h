#ifndef __UTIL2_C_DEFINITION_PRINT_VERSION2__
#define __UTIL2_C_DEFINITION_PRINT_VERSION2__
#include "util2/C/util2_api.h"
#include "util2/C/util2_extern.h"
#include <stdio.h>
#include <stdarg.h>
// #define UTIL2_PRINT_LOG_TO_FILE


UTIL2_EXTERNC_DECL_BEGIN

UTIL2_API void util2_print_lock(void);
UTIL2_API void util2_print_unlock(void);

/* All Thread Safe */
UTIL2_API void util2_va_fprintf(
    FILE*       write_into,
    const char* format, 
    va_list     arg_list
); 
UTIL2_API void util2_fprintf(FILE* write_to, const char* formatstr, ...);
UTIL2_API void util2_printf(const char* formatstr, ...);
UTIL2_API void util2_fputs(const char* str, FILE* write_to);
UTIL2_API void util2_puts(const char* str);
UTIL2_API void  util2_setfs(FILE* newfilestream);
UTIL2_API FILE* util2_getfs(void);


/* Lockless Versions. You must call util2_print_lock() before calling these. */
UTIL2_API void util2_va_fprintf_lockless(
    FILE*       write_into, 
    const char* format, 
    va_list     arg_list
);
UTIL2_API void util2_fprintf_lockless(FILE* write_to, const char* formatstr, ...);
UTIL2_API void util2_printf_lockless(const char* formatstr, ...);
UTIL2_API void util2_fputs_lockless(const char* str, FILE* write_to);
UTIL2_API void util2_puts_lockless(const char* str);

UTIL2_EXTERNC_DECL_END


#endif /* __UTIL2_C_DEFINITION_PRINT__ */
