#ifndef MYLINUX_VOLD_DISK_H
#define MYLINUX_VOLD_DISK_H

#include <cstdint>
#include <string>
#include <vector>

namespace mylinux {
namespace vold {

struct DiskInfo {
    std::string name;
    std::string sysfsPath;
    std::string devicePath;

    uint32_t majorNumber = 0;
    uint32_t minorNumber = 0;

    uint64_t sizeBytes = 0;
    uint32_t logicalBlockSize = 0;

    bool removable = false;
    bool partition = false;
    bool deviceNodeExists = false;
};

class Disk {
public:
    static std::vector<DiskInfo> scan(
        const std::string& sysBlockPath = "/sys/class/block",
        const std::string& deviceRoot = "/dev/block"
    );

    static bool readDevice(
        const std::string& name,
        DiskInfo& result,
        const std::string& sysBlockPath = "/sys/class/block",
        const std::string& deviceRoot = "/dev/block"
    );

private:
    static bool readText(
        const std::string& path,
        std::string& result
    );

    static bool readNumber(
        const std::string& path,
        uint64_t& result
    );
};

} // namespace vold
} // namespace mylinux

#endif
