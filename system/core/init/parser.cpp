#include "init.h"

#include <cassert>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <glob.h>
#include <sstream>

namespace mylinux {
namespace init {

Parser::Parser(InitConfig& config) : config_(config) {
}

std::vector<std::string> Parser::parseArguments(
    const std::string& line
) {
    std::vector<std::string> result;
    std::string current;

    char quote = 0;
    bool escaped = false;

    for (char c : line) {
        if (escaped) {
            current += c;
            escaped = false;
            continue;
        }

        if (c == '\\') {
            escaped = true;
            continue;
        }

        if (quote != 0) {
            if (c == quote) {
                quote = 0;
            } else {
                current += c;
            }
            continue;
        }

        if (c == '"' || c == '\'') {
            quote = c;
            continue;
        }

        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!current.empty()) {
                result.push_back(expandProperties(current));
                current.clear();
            }
            continue;
        }

        current += c;
    }

    if (quote != 0) {
        std::fprintf(stderr, "init: unterminated quoted argument\n");
        return {};
    }

    if (!current.empty()) {
        result.push_back(expandProperties(current));
    }

    return result;
}

bool Parser::importPath(const std::string& path) {
    std::string expanded = expandProperties(path);

    glob_t matches {};
    int result = glob(expanded.c_str(), 0, nullptr, &matches);

    if (result == GLOB_NOMATCH) {
        globfree(&matches);
        std::fprintf(
            stderr,
            "init: import matched no files: %s\n",
            expanded.c_str()
        );
        return true;
    }

    if (result != 0) {
        globfree(&matches);
        return false;
    }

    bool success = true;

    for (size_t i = 0; i < matches.gl_pathc; ++i) {
        if (!parseFile(matches.gl_pathv[i])) {
            success = false;
        }
    }

    globfree(&matches);
    return success;
}

bool Parser::parseFile(const std::string& path) {
    assert(!path.empty());

    std::ifstream file(path);

    if (!file.is_open()) {
        std::fprintf(
            stderr,
            "init: cannot open configuration: %s\n",
            path.c_str()
        );
        return false;
    }

    if (config_.imported_files.count(path) != 0) {
        std::fprintf(
            stderr,
            "init: skipping already imported file: %s\n",
            path.c_str()
        );
        return true;
    }

    config_.imported_files.insert(path);

    Action* currentAction = nullptr;
    Service* currentService = nullptr;

    std::string line;
    unsigned int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        bool indented =
            !line.empty() &&
            std::isspace(static_cast<unsigned char>(line[0]));

        size_t first = line.find_first_not_of(" \t\r\n");

        if (first == std::string::npos) {
            continue;
        }

        std::string content = line.substr(first);

        if (content[0] == '#') {
            continue;
        }

        std::vector<std::string> args = parseArguments(content);

        if (args.empty()) {
            continue;
        }

        if (args[0] == "import") {
            if (args.size() != 2) {
                std::fprintf(
                    stderr,
                    "%s:%u: invalid import directive\n",
                    path.c_str(),
                    lineNumber
                );
                return false;
            }

            currentAction = nullptr;
            currentService = nullptr;

            if (!importPath(args[1])) {
                return false;
            }

            continue;
        }

        if (!indented && args[0] == "on") {
            if (args.size() < 2) {
                return false;
            }

            config_.actions.push_back(Action {});
            currentAction = &config_.actions.back();
            currentAction->trigger = content.substr(3);

            currentService = nullptr;
            continue;
        }

        if (!indented && args[0] == "service") {
            if (args.size() < 3) {
                std::fprintf(
                    stderr,
                    "%s:%u: invalid service declaration\n",
                    path.c_str(),
                    lineNumber
                );
                return false;
            }

            config_.services.push_back(Service {});
            currentService = &config_.services.back();

            currentService->name = args[1];
            currentService->executable = args[2];

            for (size_t i = 2; i < args.size(); ++i) {
                currentService->arguments.push_back(args[i]);
            }

            currentAction = nullptr;
            continue;
        }

        if (indented && currentService != nullptr) {
            if (args[0] == "disabled") {
                currentService->disabled = true;
            } else if (args[0] == "oneshot") {
                currentService->oneshot = true;
            } else if (args[0] == "class" ||
                       args[0] == "user" ||
                       args[0] == "group" ||
                       args[0] == "seclabel") {
                // Recognized service options reserved for later.
            } else {
                std::fprintf(
                    stderr,
                    "%s:%u: unsupported service option: %s\n",
                    path.c_str(),
                    lineNumber,
                    args[0].c_str()
                );
            }

            continue;
        }

        if (indented && currentAction != nullptr) {
            Command command;
            command.args = args;
            currentAction->commands.push_back(command);
            continue;
        }

        std::fprintf(
            stderr,
            "%s:%u: unexpected directive: %s\n",
            path.c_str(),
            lineNumber,
            args[0].c_str()
        );

        return false;
    }

    return true;
}

} // namespace init
} // namespace mylinux
