#ifndef MYLINUX_VOLD_VOLUME_BASE_H
#define MYLINUX_VOLD_VOLUME_BASE_H

#include <string>
#include <mutex>
#include <cstdint>

namespace mylinux {
namespace vold {

enum class VolumeState : uint32_t {
    UNMOUNTED = 0,
    CHECKING,
    MOUNTING,
    MOUNTED,
    UNMOUNTING,
    FORMATTING,
    ERROR
};

enum class VolumeType : uint32_t {
    PUBLIC = 0,
    PRIVATE,
    EMULATED
};

class VolumeBase {
public:
    VolumeBase(
        const std::string& id,
        VolumeType type,
        const std::string& mountPath
    );

    virtual ~VolumeBase();

    VolumeBase(const VolumeBase&) = delete;
    VolumeBase& operator=(const VolumeBase&) = delete;

    const std::string& getId() const;
    const std::string& getMountPath() const;

    VolumeType getType() const;
    VolumeState getState() const;

    bool isMounted() const;

    bool mount();
    bool unmount();

protected:
    virtual bool doMount() = 0;
    virtual bool doUnmount() = 0;

    void setState(VolumeState state);

private:
    std::string id_;
    std::string mountPath_;

    VolumeType type_;

    mutable std::mutex mutex_;
    VolumeState state_;
};

} // namespace vold
} // namespace mylinux

#endif
