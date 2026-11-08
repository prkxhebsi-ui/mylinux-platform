#ifndef MYLINUX_ART_RUNTIME_IDENTITY_H
#define MYLINUX_ART_RUNTIME_IDENTITY_H

namespace mylinux {
namespace art {

class RuntimeIdentity {
public:
    static constexpr const char* name() {
        return "Android Runtime (ART)";
    }

    static constexpr const char* implementation() {
        return "MyLinux Runtime";
    }

    static constexpr const char* vendor() {
        return "MyLinux";
    }

    static constexpr const char* version() {
        return "1.0";
    }

    static constexpr const char* architecture() {
        return "arm64";
    }

    static constexpr const char* executionMode() {
        return "Interpreter";
    }
};

} // namespace art
} // namespace mylinux

#endif
