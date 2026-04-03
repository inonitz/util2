#ifndef __UTIL2_PLATFORM_DETECTION_MACRO_DEFINITON_HEADER__
#define __UTIL2_PLATFORM_DETECTION_MACRO_DEFINITON_HEADER__


/* --- 0. Constants --- */
#define UTIL2_ARCH_BIT_ORDER_LITTLE_ENDIAN (1)
#define UTIL2_ARCH_BIT_ORDER_BIG_ENDIAN (2)


/* --- 1. Operating Systems --- */
#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#   define UTIL2_OS_WINDOWS 1 /* Windows */
#   define UTIL2_OS_PLATFORM_NAME "Windows"

#elif defined(__linux__) || defined(__gnu_linux__)
#   define UTIL2_OS_LINUX 1
#   if defined(__ANDROID__)
#       define UTIL2_OS_ANDROID 1
#       define UTIL2_OS_PLATFORM_NAME "Android"
#   else
#       define UTIL2_OS_PLATFORM_NAME "Linux"
#   endif /* Linux/Derivatives */

#elif defined(__APPLE__) && defined(__MACH__)
#   include <TargetConditionals.h>
#   if TARGET_OS_IPHONE
#       define UTIL2_OS_IOS 1
#       define UTIL2_OS_PLATFORM_NAME "iOS"
#   else
#       define UTIL2_OS_MACOS 1
#       define UTIL2_OS_PLATFORM_NAME "macOS"
#   endif /* Apple */

#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
#   define UTIL2_OS_BSD 1
#   define UTIL2_OS_PLATFORM_NAME "BSD"

#elif defined(__sun) && defined(__SVR4)
#   define UTIL2_OS_SOLARIS 1
#   define UTIL2_OS_PLATFORM_NAME "Solaris"

#elif defined(__EMSCRIPTEN__)
#   define UTIL2_OS_EMSCRIPTEN 1
#   define UTIL2_OS_PLATFORM_NAME "Emscripten"

#elif defined(_AIX)
#   define UTIL2_OS_AIX 1
#   define UTIL2_OS_PLATFORM_NAME "AIX"

#elif defined(__QNX__) || defined(__QNXNTO__)
#   define UTIL2_OS_QNX 1
#   define UTIL2_OS_PLATFORM_NAME "QNX"

#elif defined(__HAIKU__)
#   define UTIL2_OS_HAIKU 1
#   define UTIL2_OS_PLATFORM_NAME "Haiku"

#else
#   define UTIL2_OS_UNKNOWN 1
#endif /* detect(OS) */


/* --- 2. Compilers --- */
#if defined(__clang__)
#   define UTIL2_COMPILER_CLANG 1
#   define UTIL2_COMPILER_NAME "Clang"

#elif defined(__MINGW32__) || defined(__MINGW64__)
#   define UTIL2_COMPILER_MINGW 1
#   define UTIL2_COMPILER_NAME "MinGW"

#elif defined(__INTEL_COMPILER) || defined(__ICC)
#   define UTIL2_COMPILER_INTEL 1
#   define UTIL2_COMPILER_NAME "Intel ICC"

#elif defined(__GNUC__) || defined(__GNUG__)
#   define UTIL2_COMPILER_GCC 1
#   define UTIL2_COMPILER_NAME "GCC"

#elif defined(_MSC_VER)
#   define UTIL2_COMPILER_MSVC 1
#   define UTIL2_COMPILER_NAME "MSVC"

#elif defined(__BORLANDC__) || defined(__CODEGEARC__)
#   define UTIL2_COMPILER_BORLAND 1
#   define UTIL2_COMPILER_NAME "Borland"

#elif defined(__xlC__) || defined(__xlc__)
#   define UTIL2_COMPILER_IBMXL 1
#   define UTIL2_COMPILER_NAME "IBM XL"

#elif defined(__TINYC__)
#   define UTIL2_COMPILER_TCC 1
#   define UTIL2_COMPILER_NAME "Tiny C"

#else
#   define UTIL2_COMPILER_UNKNOWN 1
#endif /* detect(Compiler) */


/* --- 3. Architectures --- */
#if defined(__x86_64__) || defined(_M_X64) || defined(__amd64__)
#   define UTIL2_ARCH_X64 1
#   define UTIL2_ARCH_NAME "x86_64"

#elif defined(__i386__) || defined(_M_IX86) || defined(__X86__) || defined(_X86_)
#   define UTIL2_ARCH_X86 1
#   define UTIL2_ARCH_NAME "x86"

#elif defined(__aarch64__) || defined(_M_ARM64)
#   define UTIL2_ARCH_ARM64 1
#   define UTIL2_ARCH_NAME "ARM64"

#elif defined(__arm__) || defined(_M_ARM)
#   define UTIL2_ARCH_ARM 1
#   define UTIL2_ARCH_NAME "ARM"

#elif defined(__riscv)
#   define UTIL2_ARCH_RISCV 1
#   if __riscv_xlen == 64
#       define UTIL2_ARCH_NAME "RISC-V 64"
#   else
#       define UTIL2_ARCH_NAME "RISC-V 32"
#   endif

#elif defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__)
#   define UTIL2_ARCH_WASM 1
#   if defined(__wasm64__)
#       define UTIL2_ARCH_NAME "WebAssembly 64"
#   else
#       define UTIL2_ARCH_NAME "WebAssembly 32"
#   endif

#elif defined(__mips__)
#   define UTIL2_ARCH_MIPS 1
#   if defined(__mips64)
#       define UTIL2_ARCH_NAME "MIPS64"
#   else
#       define UTIL2_ARCH_NAME "MIPS32"
#   endif

#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__) || defined(_M_PPC)
#   define UTIL2_ARCH_POWERPC 1
#   if defined(__ppc64__) || defined(__PPC64__)
#       define UTIL2_ARCH_NAME "PowerPC 64"
#   else
#       define UTIL2_ARCH_NAME "PowerPC 32"
#   endif

#elif defined(__sparc__) || defined(__sparc)
#   define UTIL2_ARCH_SPARC 1
#   if defined(__sparcv9) || defined(__sparc_v9__)
#       define UTIL2_ARCH_NAME "SPARC64"
#   else
#       define UTIL2_ARCH_NAME "SPARC32"
#   endif

#else
#   define UTIL2_ARCH_UNKNOWN 1
#endif /* detect(Architecture) */


/* --- 4. Pointer Size (16-bit vs 32-bit vs 64-bit) --- */
#if defined(__SIZEOF_POINTER__)
#   if __SIZEOF_POINTER__ == 8
#       define UTIL2_ARCH_64BIT 1
#       define UTIL2_ARCH_POINTER_SIZE 8
#   elif __SIZEOF_POINTER__ == 4
#       define UTIL2_ARCH_32BIT 1
#       define UTIL2_ARCH_POINTER_SIZE 4
#   elif __SIZEOF_POINTER__ == 2
#       define UTIL2_ARCH_16BIT 1
#       define UTIL2_ARCH_POINTER_SIZE 2
#   endif

#elif defined(_WIN64) || defined(__x86_64__) || defined(__ppc64__) || defined(__aarch64__) || defined(__mips64) || defined(__sparcv9) || defined(__wasm64__)
#   define UTIL2_ARCH_64BIT 1
#   define UTIL2_ARCH_POINTER_SIZE 8

#elif defined(_WIN32) || defined(__i386__) || defined(__IA32__) || defined(__arm__) || defined(__wasm32__) || defined(__mips__)
#   define UTIL2_ARCH_32BIT 1
#   define UTIL2_ARCH_POINTER_SIZE 4

#elif defined(_M_I86)
#   define UTIL2_ARCH_16BIT 1
#   define UTIL2_ARCH_POINTER_SIZE 2
#endif /* detect(PointerSize) */


/* --- 5. Endianness (Bit Order) --- */
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__)
#   if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#       define UTIL2_ARCH_LITTLE_ENDIAN 1
#       define UTIL2_ARCH_BIT_ORDER UTIL2_ARCH_BIT_ORDER_LITTLE_ENDIAN
#       define UTIL2_ARCH_BIT_ORDER_NAME "Little Endian"
#   elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#       define UTIL2_ARCH_BIG_ENDIAN 1
#       define UTIL2_ARCH_BIT_ORDER UTIL2_ARCH_BIT_ORDER_BIG_ENDIAN
#       define UTIL2_ARCH_BIT_ORDER_NAME "Big Endian"
#   endif /* Modern GCC and Clang provide __BYTE_ORDER__ && __ORDER_LITTLE_ENDIAN__ */

#elif defined(UTIL2_OS_WINDOWS) || defined(UTIL2_ARCH_X86) || \
        defined(UTIL2_ARCH_X64) || defined(UTIL2_ARCH_WASM)
#   define UTIL2_ARCH_LITTLE_ENDIAN 1
#   define UTIL2_ARCH_BIT_ORDER UTIL2_ARCH_BIT_ORDER_LITTLE_ENDIAN
#   define UTIL2_ARCH_BIT_ORDER_NAME "Little Endian"

#elif defined(__ARMEB__) || defined(__THUMBEB__) || defined(__AARCH64EB__) || \
        defined(__ppc__) || defined(__POWERPC__) || defined(__s390__) || defined(__sparc__)
#   define UTIL2_ARCH_BIG_ENDIAN 1
#   define UTIL2_ARCH_BIT_ORDER UTIL2_ARCH_BIT_ORDER_BIG_ENDIAN
#   define UTIL2_ARCH_BIT_ORDER_NAME "Big Endian"
#else
#   define UTIL2_ARCH_LITTLE_ENDIAN 1
#   define UTIL2_ARCH_BIT_ORDER UTIL2_ARCH_BIT_ORDER_LITTLE_ENDIAN
#   define UTIL2_ARCH_BIT_ORDER_NAME "Little Endian"
#endif


/* --- 6. Fallback Values --- */
#ifndef UTIL2_OS_PLATFORM_NAME
#   define UTIL2_OS_PLATFORM_NAME "Unknown"
#endif

#ifndef UTIL2_COMPILER_NAME
#   define UTIL2_COMPILER_NAME "Unknown"
#endif

#ifndef UTIL2_ARCH_NAME
#   define UTIL2_ARCH_NAME "Unknown"
#endif

#ifndef UTIL2_ARCH_POINTER_SIZE
#   define UTIL2_ARCH_POINTER_SIZE 0xff
#endif

#ifndef UTIL2_ARCH_BIT_ORDER
#   define UTIL2_ARCH_BIT_ORDER 0xff
#endif

#ifndef UTIL2_ARCH_BIT_ORDER_NAME
#   define UTIL2_ARCH_BIT_ORDER_NAME "Unknown"
#endif

#endif /* __UTIL2_PLATFORM_DETECTION_MACRO_DEFINITON_HEADER__ */
