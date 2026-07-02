#include "util2/C/print2.h"
#include "util2/C/macro.h"
#include "util2/C/tinycthread.h"
#include <stdio.h>
#include <stdarg.h>


#ifdef UTIL2_PRINT_LOG_TO_FILE
#   undef UTIL2_PRINT_LOG_TO_FILE
#   define UTIL2_PRINT_LOG_TO_FILE 1
#else
#   define UTIL2_PRINT_LOG_TO_FILE 0
#endif


// #define __UTIL2_GENERIC_FORMAT_BUFFER_MAX_SIZE 4096
// typedef struct __generic_format_char_buffer 
// {
//     char mem[__UTIL2_GENERIC_FORMAT_BUFFER_MAX_SIZE];
// } util2_format_buffer;


static tthread_mtx_t     s_write_lock;
static tthread_once_flag s_init_flag = ONCE_FLAG_INIT;
static FILE* s_defaultlogbuf = NULL;
static FILE* s_currlogbuffer = NULL;


static void util2_internal_init_print_state(void) {
    tthread_mtx_init(&s_write_lock, tthread_mtx_plain | tthread_mtx_recursive);
    s_defaultlogbuf = (UTIL2_PRINT_LOG_TO_FILE == 1) ? fopen("printlog.txt", "w") : NULL;
    s_currlogbuffer = (UTIL2_PRINT_LOG_TO_FILE == 1) ? s_defaultlogbuf : stdout;
    return;
}


void util2_print_lock(void) {
    tthread_call_once(&s_init_flag, util2_internal_init_print_state);
    tthread_mtx_lock(&s_write_lock);
    return;
}

void util2_print_unlock(void) {
    tthread_mtx_unlock(&s_write_lock);
    return;
}


void util2_va_fprintf(FILE* write_into, const char* format, va_list arg_list) {
    if(write_into == NULL) {
        return;
    }

    util2_print_lock();
    __unused int bytesWritten = vfprintf(write_into, format, arg_list);
    util2_print_unlock();
    return;
}

void util2_fprintf(FILE* write_into, const char* format, ...) {
    if(write_into == NULL) {
        return;
    }

    util2_print_lock();
    va_list arg_list;
    va_start(arg_list, format);
    __unused int bytesWritten = vfprintf(write_into, format, arg_list);
    va_end(arg_list);
    util2_print_unlock();
    return;
}

void util2_printf(const char* formatstr, ...) {
    util2_print_lock();

    FILE* target = s_currlogbuffer;
    va_list arg_list;
    va_start(arg_list, formatstr);
    __unused int bytesWritten = vfprintf(target, formatstr, arg_list);
    va_end(arg_list);
    util2_print_unlock();
    return;
}


void util2_fputs(const char* str, FILE* write_to) {
    if(write_to == NULL || str == NULL) {
        return;
    }
    util2_print_lock();
    __unused int bytesWritten = fputs(str, write_to);
    util2_print_unlock();
    return;
}

void util2_puts(const char* str) {
    __unused int bytesWritten = 0;
    if(str == NULL) {
        return;
    }
    util2_print_lock();
    bytesWritten = fputs(str, s_currlogbuffer);
    bytesWritten += fputs("\n", s_currlogbuffer);
    util2_print_unlock();
    return;
}


void util2_setfs(FILE* newfilestream) {
    util2_print_lock();
    s_currlogbuffer = (newfilestream == NULL) ? 
        (s_defaultlogbuf != NULL ? s_defaultlogbuf : stdout) 
        : 
        newfilestream;
    util2_print_unlock();
    return;
}

FILE* util2_getfs(void) {
    util2_print_lock();
    FILE* stream = s_currlogbuffer;
    util2_print_unlock();
    return stream;
}


/* Lockless Versions */
void util2_va_fprintf_lockless(FILE* write_into, const char* format, va_list arg_list) {
    if(write_into == NULL) {
        return;
    }
    __unused int bytesWritten = vfprintf(write_into, format, arg_list);
    return;
}

void util2_fprintf_lockless(FILE* write_into, const char* format, ...) {
    if(write_into == NULL) { 
        return;
    }
    va_list arg_list;
    va_start(arg_list, format);
    __unused int bytesWritten = vfprintf(write_into, format, arg_list);
    va_end(arg_list);
    return;
}

void util2_printf_lockless(const char* formatstr, ...) {
    va_list arg_list;
    va_start(arg_list, formatstr);
    __unused int bytesWritten = vfprintf(s_currlogbuffer, formatstr, arg_list);
    va_end(arg_list);
    return;
}

void util2_fputs_lockless(const char* str, FILE* write_to) {
    if(write_to == NULL || str == NULL) { 
        return;
    }
    __unused int bytesWritten = fputs(str, write_to);
    return;
}

void util2_puts_lockless(const char* str) {
    __unused int bytesWritten = 0;
    if(str == NULL) { 
        return;
    }
    bytesWritten  = fputs(str, s_currlogbuffer);
    bytesWritten += fputs("\n", s_currlogbuffer);
    return;
}
