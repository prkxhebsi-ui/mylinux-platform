#ifndef MYLINUX_VOLD_VOLUME_MANAGER_H
#define MYLINUX_VOLD_VOLUME_MANAGER_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "vold/VolumeBase.h"

namespace mylinux {
namespace vold {

class VolumeManager {
public:
    static VolumeManager& getInstance();

    VolumeManager(const VolumeManager&) = delete;
    VolumeManager& operator=(const VolumeManager&) = delete;

    bool addVolume(const std::shared_ptr<VolumeBase>& volume);

    bool removeVolume(const std::string& id);

    std::shared_ptr<VolumeBase> findVolume(
        const std::string& id
    ) const;

    std::vector<std::shared_ptr<VolumeBase>> getVolumes() const;

    bool mountVolume(const std::string& id);

    bool unmountVolume(const std::string& id);

    bool unmountAll();

    size_t getVolumeCount() const;

private:
    VolumeManager() = default;
    ~VolumeManager() = default;

    mutable std::mutex mutex_;

    std::vector<std::shared_ptr<VolumeBase>> volumes_;
};

} // namespace vold
} // namespace mylinux

#endif
