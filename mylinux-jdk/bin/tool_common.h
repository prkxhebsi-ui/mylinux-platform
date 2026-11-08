#ifndef MYLINUX_JDK_TOOL_COMMON_H
#define MYLINUX_JDK_TOOL_COMMON_H

#include <iostream>
#include <string>
#include <vector>

#define MYLINUX_JDK_VERSION "0.1.0-dev"
#define MYLINUX_JDK_RELEASE "17"
#define MYLINUX_JDK_NAME "MyLinux JDK"

inline void print_version(const char *tool) {
    std::cout << tool << " - " << MYLINUX_JDK_NAME
              << " " << MYLINUX_JDK_RELEASE
              << " (development " << MYLINUX_JDK_VERSION << ")\n";
}

inline void print_unavailable(const char *tool,
                              const char *backend) {
    std::cerr << tool << ": " << backend
              << " backend is not implemented yet\n";
}

inline bool has_argument(int argc, char **argv,
                         const std::string &option) {
    for (int i = 1; i < argc; ++i) {
        if (argv[i] == option)
            return true;
    }
    return false;
}

inline int common_options(int argc, char **argv,
                          const char *tool,
                          const char *usage) {
    if (has_argument(argc, argv, "--version") ||
        has_argument(argc, argv, "-version")) {
        print_version(tool);
        return 0;
    }

    if (has_argument(argc, argv, "--help") ||
        has_argument(argc, argv, "-help") ||
        has_argument(argc, argv, "-h")) {
        std::cout << "Usage: " << usage << '\n';
        return 0;
    }

    return -1;
}

#endif
