#include "VolumeManager.h"

#include <algorithm>

namespace mylinux {
namespace vold {

VolumeManager& VolumeManager::getInstance() {
    static VolumeManager instance;
    return instance;
}

bool VolumeManager::addVolume(
    const std::shared_ptr<VolumeBase>& volume
) {
    if (!volume || volume->getId().empty()) {
        return false;
    }

    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto& existing : volumes_) {
        if (existing->getId() == volume->getId()) {
            return false;
        }
    }

    volumes_.push_back(volume);

    return true;
}

bool VolumeManager::removeVolume(const std::string& id) {
    std::lock_guard<std::mutex> lock(mutex_);

    auto it = std::find_if(
        volumes_.begin(),
        volumes_.end(),
        [&id](const std::shared_ptr<VolumeBase>& volume) {
            return volume->getId() == id;
        }
    );

    if (it == volumes_.end()) {
        return false;
    }

    if ((*it)->getState() != VolumeState::UNMOUNTED &&
        (*it)->getState() != VolumeState::ERROR) {
        return false;
    }

    volumes_.erase(it);

    return true;
}

std::shared_ptr<VolumeBase> VolumeManager::findVolume(
    const std::string& id
) const {
    std::lock_guard<std::mutex> lock(mutex_);

    for (const auto& volume : volumes_) {
        if (volume->getId() == id) {
            return volume;
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<VolumeBase>>
VolumeManager::getVolumes() const {
    std::lock_guard<std::mutex> lock(mutex_);

    return volumes_;
}

bool VolumeManager::mountVolume(const std::string& id) {
    auto volume = findVolume(id);

    if (!volume) {
        return false;
    }

    return volume->mount();
}

bool VolumeManager::unmountVolume(const std::string& id) {
    auto volume = findVolume(id);

    if (!volume) {
        return false;
    }

    return volume->unmount();
}

bool VolumeManager::unmountAll() {
    auto volumes = getVolumes();

    bool success = true;

    for (auto it = volumes.rbegin(); it != volumes.rend(); ++it) {
        if ((*it)->isMounted() && !(*it)->unmount()) {
            success = false;
        }
    }

    return success;
}

size_t VolumeManager::getVolumeCount() const {
    std::lock_guard<std::mutex> lock(mutex_);

    return volumes_.size();
}

} // namespace vold
} // namespace mylinux
