#include "init.h"

#include <algorithm>
#include <cstdio>

namespace mylinux {
namespace init {

bool ServiceManager::add(const Service& service) {
    if (service.name.empty() || service.executable.empty()) {
        return false;
    }

    if (find(service.name) != nullptr) {
        std::fprintf(
            stderr,
            "init: duplicate service: %s\n",
            service.name.c_str()
        );
        return false;
    }

    services_.push_back(service);
    return true;
}

Service* ServiceManager::find(const std::string& name) {
    for (auto& service : services_) {
        if (service.name == name) {
            return &service;
        }
    }

    return nullptr;
}

const std::vector<Service>& ServiceManager::all() const {
    return services_;
}

} // namespace init
} // namespace mylinux
