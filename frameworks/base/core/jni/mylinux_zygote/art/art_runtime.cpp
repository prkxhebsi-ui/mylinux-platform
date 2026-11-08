#include "art_runtime.h"

#include <cstdio>
#include <dlfcn.h>

namespace mylinux {
namespace art {

static const char* REQUIRED_LIBRARIES[] = {
    "libart.so",
    "libnativehelper.so",
    "libandroid_runtime.so",
    "libandroidfw.so",
    "libbase.so",
    "liblog.so",
    "libc.so",
    "libdl.so"
};

std::vector<LibraryStatus> ArtRuntime::inspect() {
    std::vector<LibraryStatus> results;

    for (const char* name : REQUIRED_LIBRARIES) {
        void* handle = dlopen(name, RTLD_NOW | RTLD_LOCAL);

        LibraryStatus status;
        status.name = name;
        status.available = handle != nullptr;

        results.push_back(status);

        if (handle != nullptr) {
            dlclose(handle);
        }
    }

    return results;
}

bool ArtRuntime::isAvailable() {
    const auto results = inspect();

    for (const auto& library : results) {
        if (!library.available) {
            return false;
        }
    }

    return true;
}

void ArtRuntime::printReport() {
    const auto results = inspect();

    std::printf("MyLinux ART dependency report\n");
    std::printf("------------------------------\n");

    for (const auto& library : results) {
        std::printf(
            "%-24s %s\n",
            library.name.c_str(),
            library.available ? "AVAILABLE" : "MISSING"
        );
    }

    std::printf("------------------------------\n");
    std::printf(
        "ART dependencies: %s\n",
        isAvailable() ? "AVAILABLE" : "INCOMPLETE"
    );
}

} // namespace art
} // namespace mylinux
