#include "init.h"

#include <cstdio>
#include <cstring>
#include <cerrno>
#include <string>
#include <vector>

#include <unistd.h>
#include <sys/stat.h>

namespace mylinux {
namespace init {

static bool verifyKernelLaunch() {
    if (getpid() != 1) {
        std::fprintf(stderr, "init: rejected: PID is not 1\n");
        return false;
    }

    if (getuid() != 0 || geteuid() != 0 ||
        getgid() != 0 || getegid() != 0) {
        std::fprintf(stderr, "init: rejected: root credentials required\n");
        return false;
    }

    return true;
}

static bool createDirectory(
    const std::string& path,
    mode_t mode
) {
    if (mkdir(path.c_str(), mode) == 0) {
        return true;
    }

    if (errno == EEXIST) {
        struct stat info {};

        if (stat(path.c_str(), &info) == 0 &&
            S_ISDIR(info.st_mode)) {
            return true;
        }
    }

    std::fprintf(
        stderr,
        "init: mkdir %s: %s\n",
        path.c_str(),
        std::strerror(errno)
    );

    return false;
}

static bool initializePrimaryStorage() {
    const std::string root = "/storage/self/primary";

    if (!createDirectory("/storage", 0755))
        return false;

    if (!createDirectory("/storage/self", 0755))
        return false;

    if (!createDirectory(root, 0770))
        return false;

    const std::vector<std::string> folders = {
        "Alarms",
        "Android",
        "Android/data",
        "Android/media",
        "Android/obb",
        "Audiobooks",
        "DCIM",
        "Documents",
        "Download",
        "Movies",
        "Music",
        "Notifications",
        "Pictures",
        "Podcasts",
        "Ringtones"
    };

    for (const auto& folder : folders) {
        if (!createDirectory(root + "/" + folder, 0770)) {
            return false;
        }
    }

    struct stat info {};

    if (lstat("/sdcard", &info) == 0) {
        if (S_ISLNK(info.st_mode)) {
            char target[4096];

            ssize_t length = readlink(
                "/sdcard",
                target,
                sizeof(target) - 1
            );

            if (length >= 0) {
                target[length] = '\0';

                if (std::strcmp(
                    target,
                    "/storage/self/primary"
                ) == 0) {
                    return true;
                }
            }
        }

        std::fprintf(
            stderr,
            "init: refusing to replace existing /sdcard\n"
        );

        return false;
    }

    if (errno != ENOENT) {
        std::perror("init: lstat /sdcard");
        return false;
    }

    if (symlink(
        "/storage/self/primary",
        "/sdcard"
    ) != 0) {
        std::perror("init: create /sdcard symlink");
        return false;
    }

    puts("MyLinux init: primary storage initialized");
    return true;
}

void logMessage(
    const char* level,
    const std::string& message
) {
    std::fprintf(stderr, "[%s] init: %s\n", level, message.c_str());
}

bool parse_arguments(
    int argc,
    char** argv,
    InitOptions& options
) {
    for (int i = 1; i < argc; ++i) {
        if (std::strcmp(argv[i], "--check-config") == 0) {
            options.check_config = true;
        } else if (std::strcmp(argv[i], "--version") == 0) {
            options.show_version = true;
        } else if (std::strcmp(argv[i], "--config") == 0) {
            if (++i >= argc)
                return false;

            options.config_path = argv[i];
        } else if (std::strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return false;
        } else {
            std::fprintf(
                stderr,
                "init: unknown argument: %s\n",
                argv[i]
            );
            return false;
        }
    }

    return true;
}

void print_version() {
    puts(kVersion);
}

void print_usage(const char* program) {
    std::printf(
        "Usage: %s [options]\n"
        "  --version          Show version\n"
        "  --help             Show help\n"
        "  --check-config     Parse configuration without booting\n"
        "  --config PATH      Select init configuration\n",
        program
    );
}

bool initialize(const InitOptions& options) {
    InitConfig config;
    Parser parser(config);

    if (!parser.parseFile(options.config_path))
        return false;

    ServiceManager services;

    for (const auto& service : config.services) {
        if (!services.add(service))
            return false;
    }

    if (options.check_config) {
        std::printf(
            "init: configuration valid; actions=%zu services=%zu\n",
            config.actions.size(),
            services.all().size()
        );
        return true;
    }

    if (!verifyKernelLaunch())
        return false;

    puts("MyLinux init: kernel PID 1 authorization accepted");

    if (!initializeUeventd())
        return false;

    if (!initializePrimaryStorage())
        return false;

    ActionRunner runner(config);

    if (!runner.run("boot"))
        return false;

    puts("MyLinux init: boot actions completed");
    return true;
}

} // namespace init
} // namespace mylinux
