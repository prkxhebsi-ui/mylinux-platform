#include "AppProcessOptions.h"

#include <cstdio>

int main(int argc, char* argv[]) {
    mylinux::AppProcessOptions options;
    std::string error;

    if (!mylinux::AppProcessOptions::parse(
            argc, argv, options, error)) {

        if (error == "HELP") {
            mylinux::AppProcessOptions::printUsage(argv[0]);
            return 0;
        }

        std::fprintf(stderr, "app_process: %s\n", error.c_str());
        mylinux::AppProcessOptions::printUsage(argv[0]);
        return 2;
    }

    std::printf("MyLinux app_process launcher\n");
    std::printf("Mode: %s\n",
        options.zygote ? "zygote" :
        options.application ? "application" : "class");

    std::printf("Socket: %s\n", options.socketName.c_str());
    std::printf("Nice name: %s\n", options.niceName.c_str());
    std::printf("Classpath: %s\n", options.classPath.c_str());
    std::printf("Runtime directory: %s\n",
                options.runtimeDirectory.c_str());
    std::printf("Entry class: %s\n", options.entryClass.c_str());

    if (options.startSystemServer) {
        std::printf("System server requested: yes\n");
    }

    std::fprintf(stderr,
        "ART startup is not connected yet; refusing to launch a fake runtime.\n");

    return 1;
}
