#include "init.h"

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/mount.h>
#include <sys/stat.h>
#include <unistd.h>

namespace mylinux {
namespace init {

static bool makeDirectories(
    const std::string& path,
    mode_t mode
) {
    if (path.empty()) {
        return false;
    }

    std::string current;

    for (char c : path) {
        current += c;

        if (c == '/') {
            if (current.size() > 1 &&
                mkdir(current.c_str(), mode) != 0 &&
                errno != EEXIST) {
                return false;
            }
        }
    }

    if (mkdir(current.c_str(), mode) != 0 &&
        errno != EEXIST) {
        return false;
    }

    return true;
}

static bool builtinMkdir(
    const std::vector<std::string>& args
) {
    if (args.size() < 2) {
        return false;
    }

    mode_t mode = 0755;

    if (args.size() >= 3) {
        char* end = nullptr;
        unsigned long value = std::strtoul(
            args[2].c_str(),
            &end,
            8
        );

        if (end == args[2].c_str() || *end != '\0' ||
            value > 07777) {
            return false;
        }

        mode = static_cast<mode_t>(value);
    }

    if (!makeDirectories(args[1], mode)) {
        std::perror("init: mkdir");
        return false;
    }

    return chmod(args[1].c_str(), mode) == 0;
}

static bool builtinSymlink(
    const std::vector<std::string>& args
) {
    if (args.size() != 3) {
        return false;
    }

    if (symlink(args[1].c_str(), args[2].c_str()) != 0) {
        std::perror("init: symlink");
        return false;
    }

    return true;
}

static bool builtinSetprop(
    const std::vector<std::string>& args
) {
    if (args.size() != 3) {
        return false;
    }

    if (!PropertyService::set(args[1], args[2])) {
        std::fprintf(stderr, "init: setprop failed\n");
        return false;
    }

    return true;
}

static bool builtinMount(
    const std::vector<std::string>& args
) {
    if (args.size() < 4) {
        std::fprintf(
            stderr,
            "init: mount TYPE DEVICE TARGET [OPTIONS]\n"
        );
        return false;
    }

    unsigned long flags = 0;
    const char* data = nullptr;

    for (size_t i = 4; i < args.size(); ++i) {
        if (args[i] == "ro") {
            flags |= MS_RDONLY;
        } else if (args[i] == "rw") {
            flags &= ~MS_RDONLY;
        } else if (args[i] == "nosuid") {
            flags |= MS_NOSUID;
        } else if (args[i] == "nodev") {
            flags |= MS_NODEV;
        } else if (args[i] == "noexec") {
            flags |= MS_NOEXEC;
        } else {
            data = args[i].c_str();
        }
    }

    if (mount(
        args[2].c_str(),
        args[3].c_str(),
        args[1].c_str(),
        flags,
        data
    ) != 0) {
        std::perror("init: mount");
        return false;
    }

    return true;
}

bool executeImport(
    const std::string& path,
    InitConfig& config
) {
    Parser parser(config);
    return parser.parseFile(expandProperties(path));
}

bool executeBuiltin(
    const Command& command,
    InitConfig& config
) {
    const auto& args = command.args;

    if (args.empty()) {
        return false;
    }

    if (args[0] == "mkdir") {
        return builtinMkdir(args);
    }

    if (args[0] == "symlink") {
        return builtinSymlink(args);
    }

    if (args[0] == "setprop") {
        return builtinSetprop(args);
    }

    if (args[0] == "mount") {
        return builtinMount(args);
    }

    if (args[0] == "import") {
        if (args.size() != 2) {
            return false;
        }

        return executeImport(args[1], config);
    }

    std::fprintf(
        stderr,
        "init: unknown builtin: %s\n",
        args[0].c_str()
    );

    return false;
}

} // namespace init
} // namespace mylinux
