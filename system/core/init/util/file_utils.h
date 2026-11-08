#ifndef MYLINUX_INIT_UTIL_FILE_UTILS_H
#define MYLINUX_INIT_UTIL_FILE_UTILS_H

#include <string>

namespace mylinux {
namespace init {

bool PathExists(const std::string& path);
bool IsDirectory(const std::string& path);

bool ReadFile(
    const std::string& path,
    std::string* output
);

bool WriteFile(
    const std::string& path,
    const std::string& contents,
    int mode = 0644
);

bool EnsureDirectory(
    const std::string& path,
    int mode = 0755
);

}
}

#endif
