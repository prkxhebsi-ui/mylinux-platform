#ifndef MYLINUX_APP_PROCESS_OPTIONS_H
#define MYLINUX_APP_PROCESS_OPTIONS_H

#include <string>

namespace mylinux {

struct AppProcessOptions {
    bool zygote = false;
    bool startSystemServer = false;
    bool application = false;

    std::string socketName;
    std::string niceName;
    std::string classPath;
    std::string runtimeDirectory;
    std::string entryClass;

    static bool parse(
        int argc,
        char* argv[],
        AppProcessOptions& options,
        std::string& error
    );

    static void printUsage(const char* program);
};

}

#endif
