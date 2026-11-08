#include "logging.h"

#include <cstdio>
#include <cstdarg>
#include <cstdlib>

namespace mylinux {
namespace init {

static const char* LevelName(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG:   return "DEBUG";
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        case LogLevel::FATAL:   return "FATAL";
    }

    return "UNKNOWN";
}

void LogMessage(LogLevel level, const char* format, ...) {
    if (format == nullptr) {
        return;
    }

    std::fprintf(stderr, "[init][%s] ", LevelName(level));

    va_list args;
    va_start(args, format);
    std::vfprintf(stderr, format, args);
    va_end(args);

    std::fputc('\n', stderr);
    std::fflush(stderr);

    if (level == LogLevel::FATAL) {
        std::abort();
    }
}

}
}
