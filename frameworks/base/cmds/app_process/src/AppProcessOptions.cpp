#include "AppProcessOptions.h"

namespace mylinux {

static bool readValue(
    int& index,
    int argc,
    char* argv[],
    std::string& output,
    std::string& error,
    const char* option
) {
    if (index + 1 >= argc) {
        error = std::string("Missing value for ") + option;
        return false;
    }

    output = argv[++index];

    if (output.empty()) {
        error = std::string("Empty value for ") + option;
        return false;
    }

    return true;
}

bool AppProcessOptions::parse(
    int argc,
    char* argv[],
    AppProcessOptions& options,
    std::string& error
) {
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];

        if (arg == "--zygote") {
            options.zygote = true;
        } else if (arg == "--start-system-server") {
            options.startSystemServer = true;
        } else if (arg == "--application") {
            options.application = true;
        } else if (arg.rfind("--socket-name=", 0) == 0) {
            options.socketName = arg.substr(14);
        } else if (arg == "--socket-name") {
            if (!readValue(i, argc, argv, options.socketName,
                           error, "--socket-name")) return false;
        } else if (arg == "--nice-name") {
            if (!readValue(i, argc, argv, options.niceName,
                           error, "--nice-name")) return false;
        } else if (arg == "--classpath") {
            if (!readValue(i, argc, argv, options.classPath,
                           error, "--classpath")) return false;
        } else if (arg == "--runtime-dir") {
            if (!readValue(i, argc, argv, options.runtimeDirectory,
                           error, "--runtime-dir")) return false;
        } else if (arg == "--help" || arg == "-h") {
            error = "HELP";
            return false;
        } else if (!arg.empty() && arg[0] == '-') {
            error = "Unknown option: " + arg;
            return false;
        } else {
            options.entryClass = arg;

            for (++i; i < argc; ++i) {
                options.entryClass += " ";
                options.entryClass += argv[i];
            }

            break;
        }
    }

    if (options.zygote && options.application) {
        error = "Cannot combine --zygote and --application";
        return false;
    }

    if (!options.zygote && !options.application &&
        options.entryClass.empty()) {
        error = "No application or entry class specified";
        return false;
    }

    if (options.zygote && options.socketName.empty()) {
        error = "Zygote mode requires --socket-name";
        return false;
    }

    return true;
}

void AppProcessOptions::printUsage(const char* program) {
    fprintf(stderr,
        "Usage: %s [options] [class [arguments...]]\n"
        "\n"
        "Options:\n"
        "  --zygote                 Start in Zygote mode\n"
        "  --start-system-server    Start the system server\n"
        "  --application            Start an application\n"
        "  --socket-name NAME       Zygote socket name\n"
        "  --nice-name NAME         Process display name\n"
        "  --classpath PATH         Java classpath\n"
        "  --runtime-dir PATH       Runtime directory\n"
        "  --help                   Show this help\n",
        program
    );
}

}
