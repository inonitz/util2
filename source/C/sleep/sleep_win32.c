#include <util2/C/sleep/sleep_win32.h>
#include <stdlib.h>
#include <util2/C/macro.h>
#include <util2/C/tinycthread.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


static HANDLE        s_wintimer        = NULL;
static uint64_t      s_wintimerfreq    = 0;
static double        s_wintimerinvfreq = 0;
static tthread_mtx_t s_exitMutex;


static void closeTimerHandle() {
    CloseHandle(s_wintimer);
    return;
}

void millisleep_win32(uint32_t milliseconds) {
    Sleep(milliseconds);
    return;
}

void microsleep_win32(uint32_t microseconds) {
    const uint32_t kMicrosecondToNanosecond = 1000;
    const uint32_t kRequiredTimerIntervalWin32 = 100;
    int status = BOOL_TRUE;
    LARGE_INTEGER ft;

    /* to nanoseconds, then to 100ns intervals per the win32 spec */
    /* https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-setwaitabletimer */
    microseconds = (microseconds * kMicrosecondToNanosecond) / kRequiredTimerIntervalWin32;
    ft.QuadPart = -1 * __scast(int64_t, microseconds);  // '-' using relative time

    
    if(unlikely(s_wintimer == NULL)) {
        /* first time we pay the price for the branch, next time will be fine */
        s_wintimer = CreateWaitableTimer(NULL, TRUE, NULL);

        if(s_wintimer == NULL || atexit(closeTimerHandle) != 0) { /* Unsatisfied Allocation */
            if(tthread_mtx_init(&s_exitMutex, tthread_mtx_plain | tthread_mtx_recursive) 
                != tthread_thrd_success) {
                exit(-1); /* Fucking Catastrophic Condition, Only god knows when this'll hit */
            }
            /* Thread Safe Exit */
            while(tthread_mtx_trylock(&s_exitMutex) != tthread_thrd_success) {}
            exit(-1);
            tthread_mtx_unlock(&s_exitMutex);
        }
    }


    SetWaitableTimer(s_wintimer, &ft, 0, NULL, NULL, 0);
    WaitForSingleObject(s_wintimer, INFINITE);
    return;
}


uint64_t nowms_win32() {
    LARGE_INTEGER tmp;
    double        accurateResult = 0;

    if( unlikely(s_wintimerinvfreq == 0) ) {
        /* first time we pay the price for the branch, next time will be fine */
        QueryPerformanceFrequency(&tmp);
        s_wintimerfreq = tmp.QuadPart;
        s_wintimerinvfreq = 1.0 / s_wintimerinvfreq;
    }


    QueryPerformanceCounter(&tmp);
    accurateResult = tmp.QuadPart * 1000000;
    accurateResult *= s_wintimerinvfreq;
    return __scast(uint64_t, accurateResult);
}

