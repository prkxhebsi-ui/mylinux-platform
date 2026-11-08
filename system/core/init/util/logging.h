#ifndef MYLINUX_INIT_UTIL_LOGGING_H
#define MYLINUX_INIT_UTIL_LOGGING_H

namespace mylinux {
namespace init {

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    FATAL
};

void LogMessage(LogLevel level, const char* format, ...);

}
}

#define INIT_LOGD(...) \
    mylinux::init::LogMessage(mylinux::init::LogLevel::DEBUG, __VA_ARGS__)

#define INIT_LOGI(...) \
    mylinux::init::LogMessage(mylinux::init::LogLevel::INFO, __VA_ARGS__)

#define INIT_LOGW(...) \
    mylinux::init::LogMessage(mylinux::init::LogLevel::WARNING, __VA_ARGS__)

#define INIT_LOGE(...) \
    mylinux::init::LogMessage(mylinux::init::LogLevel::ERROR, __VA_ARGS__)

#define INIT_LOGF(...) \
    mylinux::init::LogMessage(mylinux::init::LogLevel::FATAL, __VA_ARGS__)

#endif
