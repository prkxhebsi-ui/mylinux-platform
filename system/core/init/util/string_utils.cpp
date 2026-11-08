#include "string_utils.h"

#include <cctype>

namespace mylinux {
namespace init {

std::string Trim(const std::string& value) {
    size_t first = 0;
    size_t last = value.size();

    while (first < last &&
           std::isspace(static_cast<unsigned char>(value[first]))) {
        ++first;
    }

    while (last > first &&
           std::isspace(static_cast<unsigned char>(value[last - 1]))) {
        --last;
    }

    return value.substr(first, last - first);
}

std::vector<std::string> Split(
    const std::string& value,
    char delimiter
) {
    std::vector<std::string> result;
    size_t start = 0;

    while (true) {
        size_t end = value.find(delimiter, start);

        if (end == std::string::npos) {
            result.push_back(value.substr(start));
            break;
        }

        result.push_back(value.substr(start, end - start));
        start = end + 1;
    }

    return result;
}

bool StartsWith(
    const std::string& value,
    const std::string& prefix
) {
    return value.size() >= prefix.size() &&
           value.compare(0, prefix.size(), prefix) == 0;
}

bool EndsWith(
    const std::string& value,
    const std::string& suffix
) {
    return value.size() >= suffix.size() &&
           value.compare(
               value.size() - suffix.size(),
               suffix.size(),
               suffix
           ) == 0;
}

}
}
