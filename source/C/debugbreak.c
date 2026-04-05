#include <util2/C/debugbreak.h>


void util2_debugbreak(void)
{
    UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO();
}

void util2_debugbreakif(unsigned char condition)
{
    if(boolean(condition)) {
        UTIL2_INTERNAL_DEBUG_BREAKPOINT_MACRO();
    }
}
