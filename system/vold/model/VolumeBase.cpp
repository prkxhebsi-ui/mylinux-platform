#include "vold/VolumeBase.h"

namespace mylinux {
namespace vold {

VolumeBase::VolumeBase(
    const std::string& id,
    VolumeType type,
    const std::string& mountPath
)
    : id_(id),
      mountPath_(mountPath),
      type_(type),
      state_(VolumeState::UNMOUNTED) {
}

VolumeBase::~VolumeBase() = default;

const std::string& VolumeBase::getId() const {
    return id_;
}

const std::string& VolumeBase::getMountPath() const {
    return mountPath_;
}

VolumeType VolumeBase::getType() const {
    return type_;
}

VolumeState VolumeBase::getState() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return state_;
}

bool VolumeBase::isMounted() const {
    return getState() == VolumeState::MOUNTED;
}

void VolumeBase::setState(VolumeState state) {
    std::lock_guard<std::mutex> lock(mutex_);
    state_ = state;
}

bool VolumeBase::mount() {
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (state_ != VolumeState::UNMOUNTED &&
            state_ != VolumeState::ERROR) {
            return false;
        }

        state_ = VolumeState::MOUNTING;
    }

    bool success = doMount();

    setState(success ? VolumeState::MOUNTED : VolumeState::ERROR);

    return success;
}

bool VolumeBase::unmount() {
    {
        std::lock_guard<std::mutex> lock(mutex_);

        if (state_ != VolumeState::MOUNTED) {
            return false;
        }

        state_ = VolumeState::UNMOUNTING;
    }

    bool success = doUnmount();

    setState(success ? VolumeState::UNMOUNTED : VolumeState::ERROR);

    return success;
}

} // namespace vold
} // namespace mylinux
