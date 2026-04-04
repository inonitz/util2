#ifndef __UTIL2_AGNOSTIC_DEBUG_BREAKPOINT_DEFINITION__
#define __UTIL2_AGNOSTIC_DEBUG_BREAKPOINT_DEFINITION__
#include "util2_extern.h"
#include "util2_api.h"
#include "macro.h"
/*
    Many thanks to: https://github.com/scottt/debugbreak
    Although his micro library is more thorough and battle tested,
    this is good enough for me
*/
#if !defined(NDEBUG) || defined(_DEBUG) || defined(DEBUG)
#   if defined(UTIL2_BREAKPOINT_DEFINITION_FUNCTION)
#       include "compiler_warning.h"
#       pragma message WARN("UTIL2_BREAKPOINT_DEFINITION_FUNCTION Macro Already defined somewhere else!")
#   else
#       define UTIL2_BREAKPOINT_DEFINITION_FUNCTION
#   endif /* UTIL2_BREAKPOINT_DEFINITION_FUNCTION */
#endif /* _DEBUG || DEBUG */


#ifdef UTIL2_BREAKPOINT_DEFINITION_FUNCTION
#   ifdef _MSC_VER
#      define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __debugbreak()

#   elif defined(__has_builtin) && __has_builtin(__builtin_debugtrap)
#      define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __builtin_debugtrap()

#   else
#      if defined(__i386__) || defined(__x86_64__)
#          define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile("int $3");

#      elif defined(__aarch64__)
#          define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile(".inst 0xd4200000");

#      elif defined(__arm__)
#          if defined(__thumb__)
#              define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile(".inst 0xde01");
#          else
#              define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile(".inst 0xe7f001f0");
#          endif /* if __thumb__ */

#      elif defined(__powerpc__)
#          define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile(".4byte 0x7d821008");

#      elif defined(__riscv)
#          define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() __asm__ volatile(".4byte 0x00100073");

#      elif defined(__has_include) && __has_include(<signal.h>) && __has_include(<unistd.h>)
            /* Fallback: trigger SIGTRAP */
#           include <signal.h>
#           include <unistd.h>
#           define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() raise(SIGTRAP);
#       else
#           pragma message WARN("Internal UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO is Empty, Unsupported Architecture")
#           define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO()
#      endif /* if defined(architecture) */
#   endif /* if defined(CompilerSpecific) */
#else
#   ifndef UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO
#       define UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO() (void)(0);
#   endif /* if !defined(breakpoint_macro) */
#endif /* UTIL2_BREAKPOINT_DEFINITION_FUNCTION */


UTIL2_EXTERNC_DECL_BEGIN


__force_inline inline void util2_inlinedbgbreak() {
    UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO();
}
__force_inline inline void util2_inlinedbgbreakif(unsigned char condition) {
    if(boolean(condition)) {
        UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO();
    }
    return;
}

void UTIL2_API util2_debugbreak();
void UTIL2_API util2_debugbreakif(unsigned char condition); 


UTIL2_EXTERNC_DECL_END


#endif /* __UTIL2_AGNOSTIC_DEBUG_BREAKPOINT_DEFINITION__  */
