#include "Disk.h"
#include <cstdio>

#include <algorithm>
#include <cerrno>
#include <cstdlib>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

namespace mylinux {
namespace vold {

bool Disk::readText(
    const std::string& path,
    std::string& result
) {
    FILE* file = fopen(path.c_str(), "r");

    if (file == nullptr) {
        return false;
    }

    char buffer[256];

    if (fgets(buffer, sizeof(buffer), file) == nullptr) {
        fclose(file);
        return false;
    }

    fclose(file);

    result = buffer;

    while (!result.empty() &&
           (result.back() == '\n' ||
            result.back() == '\r' ||
            result.back() == ' ' ||
            result.back() == '\t')) {
        result.pop_back();
    }

    return true;
}

bool Disk::readNumber(
    const std::string& path,
    uint64_t& result
) {
    std::string value;

    if (!readText(path, value) || value.empty()) {
        return false;
    }

    errno = 0;

    char* end = nullptr;
    unsigned long long number =
        strtoull(value.c_str(), &end, 10);

    if (errno != 0 || end == value.c_str() || *end != '\0') {
        return false;
    }

    result = static_cast<uint64_t>(number);
    return true;
}

bool Disk::readDevice(
    const std::string& name,
    DiskInfo& result,
    const std::string& sysBlockPath,
    const std::string& deviceRoot
) {
    if (name.empty() ||
        name.find('/') != std::string::npos ||
        name == "." ||
        name == "..") {
        return false;
    }

    const std::string base = sysBlockPath + "/" + name;

    struct stat info;

    if (stat(base.c_str(), &info) != 0 ||
        !S_ISDIR(info.st_mode)) {
        return false;
    }

    DiskInfo disk;
    disk.name = name;
    disk.sysfsPath = base;
    disk.devicePath = deviceRoot + "/" + name;

    // Read major:minor from sysfs.
    std::string deviceNumber;

    if (!readText(base + "/dev", deviceNumber)) {
        return false;
    }

    unsigned int majorValue = 0;
    unsigned int minorValue = 0;
    char extra = '\0';

    if (sscanf(
            deviceNumber.c_str(),
            "%u:%u%c",
            &majorValue,
            &minorValue,
            &extra
        ) != 2) {
        return false;
    }

    disk.majorNumber = majorValue;
    disk.minorNumber = minorValue;

    // Linux sysfs reports size in 512-byte sectors.
    uint64_t sectors = 0;

    if (readNumber(base + "/size", sectors)) {
        if (sectors <= UINT64_MAX / 512ULL) {
            disk.sizeBytes = sectors * 512ULL;
        }
    }

    uint64_t blockSize = 0;

    if (readNumber(
            base + "/queue/logical_block_size",
            blockSize
        ) && blockSize <= UINT32_MAX) {
        disk.logicalBlockSize =
            static_cast<uint32_t>(blockSize);
    }

    uint64_t removableValue = 0;

    if (readNumber(base + "/removable", removableValue)) {
        disk.removable = removableValue != 0;
    }

    uint64_t partitionValue = 0;

    disk.partition =
        readNumber(base + "/partition", partitionValue);

    disk.deviceNodeExists =
        access(disk.devicePath.c_str(), F_OK) == 0;

    result = disk;
    return true;
}

std::vector<DiskInfo> Disk::scan(
    const std::string& sysBlockPath,
    const std::string& deviceRoot
) {
    std::vector<DiskInfo> devices;

    DIR* directory = opendir(sysBlockPath.c_str());

    if (directory == nullptr) {
        return devices;
    }

    struct dirent* entry;

    while ((entry = readdir(directory)) != nullptr) {
        const std::string name = entry->d_name;

        if (name == "." || name == "..") {
            continue;
        }

        DiskInfo disk;

        if (readDevice(
                name,
                disk,
                sysBlockPath,
                deviceRoot
            )) {
            devices.push_back(disk);
        }
    }

    closedir(directory);

    std::sort(
        devices.begin(),
        devices.end(),
        [](const DiskInfo& a, const DiskInfo& b) {
            return a.name < b.name;
        }
    );

    return devices;
}

} // namespace vold
} // namespace mylinux
