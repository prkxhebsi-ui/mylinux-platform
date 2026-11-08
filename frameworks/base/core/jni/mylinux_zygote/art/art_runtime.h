#ifndef MYLINUX_ART_RUNTIME_H
#define MYLINUX_ART_RUNTIME_H

#include <string>
#include <vector>

namespace mylinux {
namespace art {

struct LibraryStatus {
    std::string name;
    bool available;
};

class ArtRuntime {
public:
    static std::vector<LibraryStatus> inspect();

    static bool isAvailable();

    static void printReport();
};

} // namespace art
} // namespace mylinux

#endif
