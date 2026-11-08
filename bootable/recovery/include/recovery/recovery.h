#ifndef MYLINUX_RECOVERY_H
#define MYLINUX_RECOVERY_H

#include <string>

namespace mylinux {
namespace recovery {

enum class RecoveryState {
    IDLE,
    STARTING,
    RUNNING,
    FAILED,
    FINISHED
};

struct RecoveryInfo {
    RecoveryState state = RecoveryState::IDLE;
    std::string message;
    int error_code = 0;
};

bool initialize(RecoveryInfo& info);
void report_error(RecoveryInfo& info, int code,
                  const std::string& message);

} // namespace recovery
} // namespace mylinux

#endif
