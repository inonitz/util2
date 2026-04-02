#ifndef __UTIL2_DETECT_DEBUG_BUILD_MAYBE_GOOD_ENOUGH_DEFINITION__
#define __UTIL2_DETECT_DEBUG_BUILD_MAYBE_GOOD_ENOUGH_DEFINITION__
#include "compiler_warning.h"


#   ifndef UTIL2_DEBUG_BUILD
#      define UTIL2_DEBUG_BUILD -1
#   endif /* UTIL2_DEBUG_BUILD */
#   ifndef UTIL2_DEBUG_CONDITIONAL
#      define UTIL2_DEBUG_CONDITIONAL(OPTION_A_IF_DEBUG, OPTION_B_IF_NOT_DEBUG) (-1)
#   endif /* UTIL2_DEBUG_CONDITIONAL */
#   ifndef UTIL2_ON_DEBUG_EVAL
#      define UTIL2_ON_DEBUG_EVAL(...)
#   endif /* UTIL2_ON_DEBUG_EVAL */
#   ifndef UTIL2_ON_DEBUG_DO
#      define UTIL2_ON_DEBUG_DO(...) do {} while(0);
#   endif /* UTIL2_ON_DEBUG_DO */


#   if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
#       undef UTIL2_DEBUG_BUILD
#       undef UTIL2_DEBUG_CONDITIONAL
#       undef UTIL2_ON_DEBUG_EVAL
#       undef UTIL2_ON_DEBUG_DO
#       define UTIL2_DEBUG_BUILD 1
#       define UTIL2_DEBUG_CONDITIONAL(OPTION_A_IF_DEBUG, OPTION_B_IF_NOT_DEBUG) (OPTION_A_IF_DEBUG)
#       define UTIL2_ON_DEBUG_EVAL(...) (__VA_ARGS__)
#       define UTIL2_ON_DEBUG_DO(...) { __VA_ARGS__ }

#   else /* Release Build OR Release Build with Debug info (Maybe? lol) */
#       undef UTIL2_DEBUG_BUILD
#       undef UTIL2_DEBUG_CONDITIONAL
#       define UTIL2_DEBUG_CONDITIONAL(OPTION_A_IF_DEBUG, OPTION_B_IF_NOT_DEBUG) (OPTION_B_IF_NOT_DEBUG)
#       define UTIL2_DEBUG_BUILD 0
#   endif /* DetectDebugBuild() */


#if UTIL2_DEBUG_BUILD == -1
#   pragma message WARN("Somehow util2 didn't detect a Debug/Release Configuration")
#endif /* UTIL2_DEBUG_BUILD == Undefined */

#ifndef UTIL2_RELEASE_BUILD
#   define UTIL2_RELEASE_BUILD ! !!(UTIL2_DEBUG_BUILD)
#endif /* UTIL2_RELEASE_BUILD */


#endif /* __UTIL2_DETECT_DEBUG_BUILD_MAYBE_GOOD_ENOUGH_DEFINITION__ */
