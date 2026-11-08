#include "art_runtime.h"

int main() {
    mylinux::art::ArtRuntime::printReport();
    return mylinux::art::ArtRuntime::isAvailable() ? 0 : 1;
}
