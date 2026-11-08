#ifndef MYLINUX_INIT_UTIL_STRING_UTILS_H
#define MYLINUX_INIT_UTIL_STRING_UTILS_H

#include <string>
#include <vector>

namespace mylinux {
namespace init {

std::string Trim(const std::string& value);

std::vector<std::string> Split(
    const std::string& value,
    char delimiter
);

bool StartsWith(
    const std::string& value,
    const std::string& prefix
);

bool EndsWith(
    const std::string& value,
    const std::string& suffix
);

}
}

#endif
