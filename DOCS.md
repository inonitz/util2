
# Rudimentary Documentation

* Basic Information regarding each header, use cases, etc...  

0. [aligned_malloc.h](include/util2/C/aligned_malloc.h):  
    allocate a memory block that is aligned to a specific address multiple (4KiB Page, Cache Line, Etc...)

1. [base_type.h](include/util2/C/base_type.h):  
    Basic Cross Platform Types

2. [buffer.h](include/util2/C/buffer.h):  
    Implementation of a C++ like Vector in C using Macros

3. [compiler_warning.h](include/util2/C/compiler_warning.h):  
    Cross Platform compiler warning Macro

4. [file.h](include/util2/C/file.h):  
    load a file to an allocated memory region

5. [ifcrash2.h](include/util2/C/ifcrash2.h):  
    an if statement that terminates the program when its condition is true  
    Prints out information regarding file of origin, line-of-code, custom message, etc...

6. [image2.h](include/util2/C/image2.h):  
    loads/unloads an image using AVX/SSE

7. [macro.h](include/util2/C/macro.h):  
    Cross-Platform C Macros across GCC/Clang/GCC-Like/MSVC

8. [marker4.h](include/util2/C/marker4.h):  
    Used mostly for debugging without a debugger -  
    prints to stdout/log file a debug message containing file:line-of-code:custom_message

9. [murmur64a.h](include/util2/C/murmur64a.h):  
    Implementation of an 8 byte murmur-hash, specifically version [MurmurHash64A](https://github.com/hhrhhr/MurmurHash-for-Lua/blob/master/MurmurHash64A.c)

10. [print.h](include/util2/C/print.h):  
    Common Thread-Safe implementation of printf, can also log to file by default (enable using UTIL2_PRINT_LOG_TO_FILE)

11. [sleep.h](include/util2/C/sleep.h):  
    Cross-platform implementation of sleep for the current thread (Common-Linux, MacOS, Windows)

12. [static_assert.h](include/util2/C/static_assert.h):  
    Cross-platform static_assert implementation  

13. [string.h](include/util2/C/string.h):  
    Provides common functions in [cstring](https://en.cppreference.com/w/cpp/header/cstring.html), also provides ```readtsc()```, ```count_trailing_zeros()```, etc...

14. [thread_sleep.h](include/util2/C/thread_sleep.h):  
    std/posix implementation of thread_sleep(nanoseconds)

15. [varg_count.h](include/util2/C/varg_count.h):  
    Cross-Platform implementation of argument counting using a macro 'UTIL2_ARG_COUNT'

16. [aligned_malloc.hpp](include/util2/C/aligned_malloc.hpp):  
    C++ version of [aligned_malloc.h](include/util2/C/aligned_malloc.h)

17. [include/util2/array_view.hpp](include/util2/array_view.hpp):  
    An Owning/Non-Owning Buffer Range | very similar to std::span

18. [include/util2/bufferptr.hpp](include/util2/bufferptr.hpp):  
    Manages a pointer to a new/malloc'd/Custom memory region, with optional Explicit Control over de-allocation

19. [include/util2/file.hpp)](include/util2/file.hpp):  
    C++ version of [file.h](include/util2/C/file.h), with added ```current_path()``` for C++17 and above

20. [include/util2/flat_hash.hpp](include/util2/flat_hash.hpp):  
    Implementation of a hash-table, definitely not as good as googles' [flat_hash_map](https://abseil.io/docs/cpp/guides/container)

21. [include/util2/hash.hpp](include/util2/hash.hpp):  
    Hash Class - uses [MurmurHash64A](https://github.com/hhrhhr/MurmurHash-for-Lua/blob/master/MurmurHash64A.c) under the hood to generate hashes

22. [include/util2/pool.hpp)](include/util2/pool.hpp):  
    Implementation of a Static Pool Allocation Scheme

23. [include/util2/print.hpp](include/util2/print.hpp):  
    C++ version of [print.h](include/util2/C/print.h) - It is incomplete. Do not use

24. [include/util2/random.hpp](include/util2/random.hpp):  
    Random number generator for all base types -  
    initialized with a random hardware seed at [Static Initialization Time](https://stackoverflow.com/a/17785008)

25. [include/util2/runtime_constptr.hpp](include/util2/runtime_constptr.hpp):  
    I needed a way to initialize a constant pointer during runtime once, and only once, s.t any further modifications will not work

26. [include/util2/string.hpp](include/util2/string.hpp):  
    Provides common functions in [cstring](https://en.cppreference.com/w/cpp/header/cstring.html), also provides ```readtsc()```, ```count_trailing_zeros()```, etc...

27. [include/util2/time.hpp](include/util2/time.hpp):  
    Provides the ```util2::Time``` namespaces, which contains classes for calculating time durations, average-Tick-Duration, etc...

28. [include/util2/vec2.hpp](include/util2/vec2.hpp):  
    Vector, Matrix Math Operations in Row-Major Memory Order, using float-only ```vec2```, ```vec3```, ```vec4```, ```mat2x2``` ```mat4x4``` classes and associated functions, such as ```identity()```, ```translate()```, ```transpose()```, ```perspective()```, etc...  
    was primarily used for 3D Graphics
