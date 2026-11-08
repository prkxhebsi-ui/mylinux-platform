#ifndef MYLINUX_DALVIK_LOGGING_H
#define MYLINUX_DALVIK_LOGGING_H

typedef enum {
    DALVIK_LOG_VERBOSE,
    DALVIK_LOG_DEBUG,
    DALVIK_LOG_INFO,
    DALVIK_LOG_WARNING,
    DALVIK_LOG_ERROR
} DalvikLogLevel;

void dalvikLogWrite(
    DalvikLogLevel level,
    const char *tag,
    const char *message
);

void dalvikLogSetLevel(DalvikLogLevel level);

#endif
