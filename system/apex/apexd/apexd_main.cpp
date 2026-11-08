#include "apexd.h"
#include "apex_constants.h"

#include <cstdio>
#include <cstring>

static void PrintUsage(const char* program) {
    std::printf("Usage: %s [option]\n", program);
    std::printf("Options:\n");
    std::printf("  --version    Show daemon version\n");
    std::printf("  --scan       Scan system and data APEX directories\n");
    std::printf("  --help       Show this help\n");
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (std::strcmp(argv[1], "--version") == 0) {
            std::printf("MyLinux apexd %s\n", APEX_VERSION);
            return 0;
        }

        if (std::strcmp(argv[1], "--help") == 0) {
            PrintUsage(argv[0]);
            return 0;
        }

        if (std::strcmp(argv[1], "--scan") != 0) {
            PrintUsage(argv[0]);
            return 2;
        }
    }

    Apexd daemon;
    return daemon.Run();
}
