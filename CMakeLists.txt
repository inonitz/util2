cmake_minimum_required(VERSION 3.14)
project(util2 
    VERSION 2.0.0
    DESCRIPTION "C/C++ Cross-Platform Utillity Library"
    LANGUAGES C CXX
)


set(SOURCES
    source/C/aligned_malloc.c
    source/C/buffer.c
    source/C/file.c
    source/C/ifcrash2.c
    source/C/image2.c
    source/C/marker4.c
    source/C/print.c
    source/C/sleep.c
    source/C/stb_image.c
    source/C/thread_sleep.c
    source/C/tinycthread.c
    
    source/aligned_malloc.cpp
    source/file.cpp
    source/pool.cpp
    source/print.cpp
    source/random.cpp
    source/time.cpp
    source/vec2.cpp
)

set(HEADERS
    include/util2/C/aligned_malloc.h
    include/util2/C/base_type.h
    include/util2/C/buffer.h
    include/util2/C/compiler_warning.h
    include/util2/C/file.h
    include/util2/C/ifcrash2.h
    include/util2/C/image2.h
    include/util2/C/macro.h
    include/util2/C/marker4.h
    include/util2/C/murmur64a.h
    include/util2/C/print.h
    include/util2/C/sleep.h
    include/util2/C/static_assert.h
    include/util2/C/stb_image.h
    include/util2/C/string.h
    include/util2/C/thread_sleep.h
    include/util2/C/tinycthread.h
    include/util2/C/util2_api.h
    include/util2/C/util2_extern.h
    include/util2/C/varg_count.h

    include/util2/aligned_malloc.hpp
    include/util2/array_view.hpp
    include/util2/bufferptr.hpp
    include/util2/file.hpp
    include/util2/flat_hash.hpp
    include/util2/hash.hpp
    include/util2/pool.hpp
    include/util2/print.hpp
    include/util2/random.hpp
    include/util2/string.hpp
    include/util2/time.hpp
    include/util2/type_trait.hpp
    include/util2/vec2.hpp
)


if(BUILD_SHARED_LIBS)
    add_library(util2 SHARED)
    target_compile_definitions(util2 PUBLIC UTIL2_EXPORTS)
else()
    add_library(util2 STATIC)
    target_compile_definitions(util2 PUBLIC UTIL2_STATIC_DEFINE)
endif()

add_library(UTIL2::util2 ALIAS util2)
target_include_directories(util2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(util2 PRIVATE ${SOURCES})
target_sources(util2 PRIVATE ${HEADERS})


# The minimum C/C++ versions required for the library
target_compile_features(util2 PUBLIC cxx_std_17)
target_compile_features(util2 PUBLIC c_std_11)
if(BUILD_SHARED_LIBS)
    set_target_properties(util2 PROPERTIES 
        C_VISIBILITY_PRESET       hidden
        CXX_VISIBILITY_PRESET     hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
endif()




if(DEFINED CMAKE_SYSTEM_NAME)
    set(PLATFORM_SPECIFIC_FILES "")
    set(PLATFORM_SPECIFIC_LINKING "")


    if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
        set(PLATFORM_SPECIFIC_FILES
            include/util2/C/sleep/sleep_linux.h 
            source/C/sleep/sleep_linux.c
        )
        set(PLATFORM_SPECIFIC_LINKING pthread)
    endif()
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set(PLATFORM_SPECIFIC_FILES
            include/util2/C/sleep/sleep_osx.h 
            source/C/sleep/sleep_osx.c
        )
        set(PLATFORM_SPECIFIC_LINKING pthread)
    endif()
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        set(PLATFORM_SPECIFIC_FILES
            include/util2/C/sleep/sleep_win32.h 
            source/C/sleep/sleep_win32.c
        )
    endif()


    target_sources(util2 PRIVATE ${PLATFORM_SPECIFIC_FILES})
    target_link_libraries(util2 PRIVATE ${PLATFORM_SPECIFIC_LINKING})
else()
    message(STATUS "\n
        [util2] -> 
            CMake Variable 'CMAKE_SYSTEM_NAME' Doesn't exist. 
            If cross Compiling, make sure to define explicitly for your target platform.
            !Cannot proceed with Build!"
    )
endif()
