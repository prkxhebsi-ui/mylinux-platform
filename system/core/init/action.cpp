#include "init.h"

#include <cstdio>
#include <cstring>

namespace mylinux {
namespace init {

ActionRunner::ActionRunner(InitConfig& config)
    : config_(config) {
}

bool ActionRunner::run(const std::string& trigger) {
    bool success = true;

    for (auto& action : config_.actions) {
        if (action.trigger != trigger) {
            continue;
        }

        std::printf(
            "init: executing action: %s\n",
            trigger.c_str()
        );

        for (const auto& command : action.commands) {
            if (!executeBuiltin(command, config_)) {
                std::fprintf(
                    stderr,
                    "init: action command failed: %s\n",
                    command.args.empty()
                        ? "(empty)"
                        : command.args[0].c_str()
                );

                success = false;
            }
        }
    }

    return success;
}

} // namespace init
} // namespace mylinux
