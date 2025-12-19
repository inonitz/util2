
## Rudimentry Documentation

* This doucmentation doesn't cover all files, but does provide demonstrations for most files.  

1. include/C/base_type:
    Basic Cross Platform Types

2. include/C/buffer.h:
    Implementation of a C++ like Vector in C using Macros

3. include/C/compiler_warning.h:
    Cross Platform compiler warning Macro

4. include/C/file.h:
    load a file
    Get current path

5. include/C/ifcrash2.h:
    if statement to check for error conditions - if met, will crash the program.
    Prints out information regarding file of origin, loc, custom messages, etc

6. include/C/image2.h:
    loads/unloads an image using AVX/SSE

7. include/C/macro.h:
    Cross-Platform C Macros across GCC/Clang/GCC-Like/MSVC

8. include/C/marker4.h:
    Used mostly for debugging without a debugger -  
    prints to stdout/log file a debug message containing the file:loc:custom_message

9. include/C/murmur64a.h:
    Implementation of an 8 byte murmur-hash

10. include/C/print.h:
    Common Thread-Safe implementation of printf, can also log to file by default (enable using UTIL2_PRINT_LOG_TO_FILE)

11. include/C/sleep.h:
    Cross-platform implementation of sleep for the current thread

12. include/C/static_assert.h:
    Cross-platform static_assert implementation  

13. include/C/string.h:
    Contains common std cstring utilities e.g memcpy, memset

14. include/C/thread_sleep.h:
    std/posix implementation of thread_sleep(nanoseconds)

15. include/C/varg_count.h:
    Cross-Platform implementation of argument counting using a macro 'UTIL2_ARG_COUNT'

16. include/aligned_malloc.hpp:
    C++ version of aligned_malloc.h

17.