#ifndef MYLINUX_LOG_H
#define MYLINUX_LOG_H

#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

enum mylinux_log_priority {
    MYLOG_UNKNOWN = 0,
    MYLOG_DEFAULT = 1,
    MYLOG_VERBOSE = 2,
    MYLOG_DEBUG = 3,
    MYLOG_INFO = 4,
    MYLOG_WARN = 5,
    MYLOG_ERROR = 6,
    MYLOG_FATAL = 7,
    MYLOG_SILENT = 8
};

int mylog_set_min_priority(int priority);
int mylog_get_min_priority(void);
int mylog_write(int priority, const char *tag,
                const char *message);
int mylog_vprintf(int priority, const char *tag,
                  const char *format, va_list args);
int mylog_printf(int priority, const char *tag,
                 const char *format, ...);
const char *mylog_priority_name(int priority);

#ifdef __cplusplus
}
#endif

#endif
