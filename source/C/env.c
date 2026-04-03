#include <util2/C/env.h>
#include <util2/C/platform.h>
#include <util2/C/compiler_warning.h>
#include <stdlib.h>


#if defined(UTIL2_OS_WINDOWS) && UTIL2_OS_WINDOWS == 1
static i32 util2_putenv_win32(const char* str);
static i32 util2_setenv_win32(
    const char* name, 
    const char* val, 
    bool_t      overwrite
);
#elif defined(UTIL2_OS_LINUX) && UTIL2_OS_LINUX == 1
static i32 util2_putenv_nix(const char* str);
static i32 util2_setenv_nix(
    const char* name, 
    const char* val, 
    bool_t      overwrite
);
#else
#   pragma WARN("Couldn't Detect Platform for internal util2 env functions (see util2/include/util2/C/env.h)\n")
#endif /* */


/* 
    Only static variables/Dynamically allocated/program (lifetime) constant variables 
    should be passed to putenv 
    See: https://stackoverflow.com/a/5876818
*/
i32 util2_putenv(const char* str)
{
#if defined(UTIL2_OS_WINDOWS) && UTIL2_OS_WINDOWS == 1
    return util2_putenv_win32(str);
#elif defined(UTIL2_OS_LINUX) && UTIL2_OS_LINUX == 1
    return util2_putenv_nix(str);
#else
#   pragma WARN("Couldn't Detect Platform for util2_putenv (see util2/include/util2/C/env.h)\n")
    return 0xff;
#endif
}


i32 util2_setenv(const char* name, const char* val, bool_t replace_if_exists)
{
#if defined(UTIL2_OS_WINDOWS) && UTIL2_OS_WINDOWS == 1
    return util2_setenv_win32(name, val, replace_if_exists);
#elif defined(UTIL2_OS_LINUX) && UTIL2_OS_LINUX == 1
    return util2_setenv_nix(name, val, replace_if_exists);
#else
#   pragma WARN("Couldn't Detect Platform for util2_setenv (see util2/include/util2/C/env.h)\n")
    return 0xff;
#endif
}




#if defined(UTIL2_OS_WINDOWS) && UTIL2_OS_WINDOWS == 1

i32 util2_putenv_win32(const char* str)
{
    return _putenv((char*)str);
}

i32 util2_setenv_win32(const char* name, const char* val, bool_t overwrite)
{
    i32 errcode = 0;
    if(!overwrite) 
    {
        u64 envsize = 0;
        errcode = getenv_s(&envsize, NULL, 0, name);
        if(errcode || envsize) {
            return errcode;
        }
    }
    return _putenv_s(name, val);
}

#endif /* UTIL2_OS_WINDOWS */


#if defined(UTIL2_OS_LINUX) && UTIL2_OS_LINUX == 1

i32 util2_putenv_nix(const char* str)
{
    return putenv((char*)str);
}

i32 util2_setenv_nix(
    const char* name, 
    const char* val, 
    bool_t      overwrite
) {
    return setenv(name, val, overwrite);
}

#endif /* UTIL2_OS_LINUX */

