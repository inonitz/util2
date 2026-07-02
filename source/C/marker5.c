#include "util2/C/marker5.h"


// #if UTIL2_MARKER_FLAG_DEFINE_IMPLEMENTATION == 1
// #   if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)
// #       include <time.h>
// #   else
// #       include "util2/C/compiler_warning.h"
// #       pragma message WARN("Cannot use <time.h> - No support available for it")
// #   endif
// #   include "util2/C/macro.h"
// #   include <stdatomic.h>
// #   include <stdio.h>
// #   include <stdlib.h>
// #   include <stdarg.h>
// #   include <pthread.h>
// #if defined __clang__ && defined _WIN32 && defined __MINGW64__
// #   include <pthread_time.h>
// #endif


#if UTIL2_MARKER_FLAG_DEFINE_IMPLEMENTATION == 1
#   include "util2/C/macro.h"
#   include "util2/C/print2.h"
#   include <stdatomic.h>
#   include <stdio.h>
#   include <stdarg.h>


static alignsz(64) atomic_uint_least64_t s_markflag = 0;


void util2_marker_flag(
    const char*   file_macro, 
    unsigned long line_macro, 
    const char*   formatstr, 
    ...
) {
    util2_print_lock();


    FILE*              currfs = util2_getfs();
    unsigned long long logid  = atomic_fetch_add_explicit(&s_markflag, 1, memory_order_relaxed);

    util2_fprintf(currfs, "[%6llu] %s:%-4u [ADDITIONAL_INFO] ", 
        logid, 
        file_macro, 
        line_macro
    );

    va_list fmt_list;
    va_start(fmt_list, formatstr);
    util2_va_fprintf(currfs, formatstr, fmt_list);
    va_end(fmt_list);


#if UTIL2_MARKER_FLAG_INCLUDE_NEWLINE_AT_END == 1
    util2_fputs("\n", currfs);
#endif


    util2_print_unlock();
    return;
}


#endif /* UTIL2_MARKER_FLAG_DEFINE_IMPLEMENTATION */