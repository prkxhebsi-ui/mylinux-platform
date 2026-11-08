#define _POSIX_C_SOURCE 200809L

#include "mylinux_log.h"

#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MYLOG_TAG_LIMIT 64
#define MYLOG_MESSAGE_LIMIT 2048

static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;
static int minimum_priority = MYLOG_VERBOSE;

static int priority_valid(int priority)
{
    return priority >= MYLOG_UNKNOWN &&
           priority <= MYLOG_SILENT;
}

const char *mylog_priority_name(int priority)
{
    switch (priority) {
    case MYLOG_UNKNOWN:  return "UNKNOWN";
    case MYLOG_DEFAULT:  return "DEFAULT";
    case MYLOG_VERBOSE:  return "VERBOSE";
    case MYLOG_DEBUG:    return "DEBUG";
    case MYLOG_INFO:     return "INFO";
    case MYLOG_WARN:     return "WARN";
    case MYLOG_ERROR:    return "ERROR";
    case MYLOG_FATAL:    return "FATAL";
    case MYLOG_SILENT:   return "SILENT";
    default:             return "INVALID";
    }
}

int mylog_set_min_priority(int priority)
{
    if (!priority_valid(priority))
        return -EINVAL;

    if (pthread_mutex_lock(&log_mutex) != 0)
        return -EDEADLK;

    minimum_priority = priority;

    if (pthread_mutex_unlock(&log_mutex) != 0)
        return -EDEADLK;

    return 0;
}

int mylog_get_min_priority(void)
{
    int result = MYLOG_VERBOSE;

    if (pthread_mutex_lock(&log_mutex) != 0)
        return result;

    result = minimum_priority;

    (void)pthread_mutex_unlock(&log_mutex);
    return result;
}

static void copy_tag(char *destination, size_t capacity,
                     const char *source)
{
    size_t length;

    if (capacity == 0)
        return;

    if (source == NULL || source[0] == '\0')
        source = "MyLinux";

    length = strlen(source);
    if (length >= capacity)
        length = capacity - 1;

    memcpy(destination, source, length);
    destination[length] = '\0';
}

static void make_timestamp(char *buffer, size_t capacity)
{
    struct timespec now;
    struct tm local;

    if (capacity == 0)
        return;

    if (clock_gettime(CLOCK_REALTIME, &now) != 0) {
        (void)snprintf(buffer, capacity, "time-unavailable");
        return;
    }

    if (localtime_r(&now.tv_sec, &local) == NULL) {
        (void)snprintf(buffer, capacity, "time-unavailable");
        return;
    }

    (void)snprintf(buffer, capacity,
                   "%04d-%02d-%02dT%02d:%02d:%02d.%03ld",
                   local.tm_year + 1900,
                   local.tm_mon + 1,
                   local.tm_mday,
                   local.tm_hour,
                   local.tm_min,
                   local.tm_sec,
                   now.tv_nsec / 1000000L);
}

int mylog_write(int priority, const char *tag,
                const char *message)
{
    char safe_tag[MYLOG_TAG_LIMIT];
    char timestamp[48];
    int threshold;
    int result;

    if (!priority_valid(priority))
        return -EINVAL;

    if (priority == MYLOG_SILENT)
        return 0;

    if (message == NULL)
        return -EINVAL;

    threshold = mylog_get_min_priority();
    if (priority < threshold)
        return 0;

    copy_tag(safe_tag, sizeof(safe_tag), tag);
    make_timestamp(timestamp, sizeof(timestamp));

    if (pthread_mutex_lock(&log_mutex) != 0)
        return -EDEADLK;

    result = fprintf(stderr, "%s %s/%s: %s\n",
                     timestamp,
                     mylog_priority_name(priority),
                     safe_tag,
                     message);

    if (result >= 0 && fflush(stderr) != 0)
        result = -1;

    (void)pthread_mutex_unlock(&log_mutex);

    if (result < 0)
        return errno != 0 ? -errno : -EIO;

    return result;
}

int mylog_vprintf(int priority, const char *tag,
                  const char *format, va_list args)
{
    char message[MYLOG_MESSAGE_LIMIT];
    va_list copy;
    int result;

    if (format == NULL)
        return -EINVAL;

    va_copy(copy, args);
    result = vsnprintf(message, sizeof(message), format, copy);
    va_end(copy);

    if (result < 0)
        return -EIO;

    if ((size_t)result >= sizeof(message)) {
        static const char suffix[] = "...[truncated]";
        size_t suffix_length = sizeof(suffix) - 1;
        size_t offset = sizeof(message) - suffix_length - 1;

        memcpy(message + offset, suffix, suffix_length + 1);
    }

    return mylog_write(priority, tag, message);
}

int mylog_printf(int priority, const char *tag,
                 const char *format, ...)
{
    va_list args;
    int result;

    va_start(args, format);
    result = mylog_vprintf(priority, tag, format, args);
    va_end(args);

    return result;
}
