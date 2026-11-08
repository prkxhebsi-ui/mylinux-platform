#include "recovery/recovery.h"

namespace mylinux {
namespace recovery {

bool initialize(RecoveryInfo& info) {
    info.state = RecoveryState::STARTING;
    info.error_code = 0;
    info.message = "Recovery initialization started";

    info.state = RecoveryState::RUNNING;
    info.message = "Recovery component initialized";

    return true;
}

void report_error(RecoveryInfo& info, int code,
                  const std::string& message) {
    info.state = RecoveryState::FAILED;
    info.error_code = code;
    info.message = message;
}

} // namespace recovery
} // namespace mylinux
