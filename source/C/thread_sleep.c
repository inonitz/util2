#include "util2/C/thread_sleep.h"


#if defined(linux) || defined(__linux__)
#   if defined(_POSIX_C_SOURCE) && (_POSIX_C_SOURCE >= 199309L)
#       include <time.h>
#   else
#       include "util2/C/compiler_warning.h"
#       pragma message WARN("Cannot use <time.h> - No support available for it")
#   endif
#   include <pthread.h>
#   define __UTIL2_DEFINITION_THREAD_SLEEP_USE_POSIX__ 1
#elif defined(_WIN32) || defined(_WIN64)
#   if defined(__MINGW64__)
#       include <pthread.h>
#       include <pthread_time.h>
#       define __UTIL2_DEFINITION_THREAD_SLEEP_USE_POSIX__ 1
#   else
#       include <threads.h>
#       define __UTIL2_DEFINITION_THREAD_SLEEP_USE_POSIX__ 0
#   endif
#endif


i32 util2_thread_sleep(i32 duration_nanoseconds)
{
    const i32 kNanosecondsLimit = 1000 * 1000 * 1000; /* Exactly 1 second */
    /* 
        Given 100ns per loop iteration, comes out to ~399 seconds 
        At that point, just use microsleep/normal sleep
    */
    const u64 kTimeOutCounterLimit = 4294967295;

    struct timespec sleep_request = (struct timespec){
        .tv_sec = duration_nanoseconds / kNanosecondsLimit,
        .tv_nsec = duration_nanoseconds % kNanosecondsLimit
    };
    struct timespec remaining_sleep = (struct timespec){
        .tv_sec = 0,
        .tv_nsec = 0
    };
    u64 timeOutCounter = 0;
    i32 status = 0xff;


#if __UTIL2_DEFINITION_THREAD_SLEEP_USE_POSIX__ == 1
    status = nanosleep(&sleep_request, &remaining_sleep); /* Early Exit */
    while( status < 0 && (timeOutCounter < kTimeOutCounterLimit) ) {
        sleep_request = remaining_sleep;
        remaining_sleep = (struct timespec){0, 0};
        ++timeOutCounter;

        status = nanosleep(&sleep_request, &remaining_sleep);
    }
#else
    status = thrd_sleep(&sleep_request, &remaining_sleep); /* Early Exit */
    while( status < 0 && (timeOutCounter < kTimeOutCounterLimit) ) {
        sleep_request = remaining_sleep;
        remaining_sleep = (struct timespec){0, 0};
        ++timeOutCounter;

        status = thrd_sleep(&sleep_request, &remaining_sleep);
    }
#endif


    status = (status == 0) && (timeOutCounter < kTimeOutCounterLimit);
    return status ? 0 : -1;
}


#undef __UTIL2_DEFINITION_THREAD_SLEEP_USE_POSIX__
