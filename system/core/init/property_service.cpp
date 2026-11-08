#include "init.h"

#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>

namespace mylinux {
namespace init {

static std::map<std::string, std::string> properties;

bool PropertyService::set(
    const std::string& name,
    const std::string& value
) {
    if (name.empty() || name.size() > 128 || value.size() > 4096) {
        return false;
    }

    properties[name] = value;
    return true;
}

std::string PropertyService::get(const std::string& name) {
    auto it = properties.find(name);

    if (it != properties.end()) {
        return it->second;
    }

    const char* env = std::getenv(name.c_str());
    return env ? env : "";
}

bool PropertyService::contains(const std::string& name) {
    return properties.find(name) != properties.end();
}

std::string expandProperties(const std::string& input) {
    std::string output;

    for (size_t i = 0; i < input.size();) {
        if (input[i] == '$' &&
            i + 1 < input.size() &&
            input[i + 1] == '{') {

            size_t end = input.find('}', i + 2);

            if (end == std::string::npos) {
                output.append(input.substr(i));
                break;
            }

            std::string key = input.substr(i + 2, end - i - 2);
            output += PropertyService::get(key);
            i = end + 1;
        } else {
            output += input[i++];
        }
    }

    return output;
}

} // namespace init
} // namespace mylinux
