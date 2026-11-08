#include <unistd.h>
#include <stdint.h>
#include "mylinux_jdk_native.h"

const char *mylinux_jdk_native_version(void) {
    return "MyLinux JDK Native 0.1.0-dev";
}

int mylinux_jdk_pointer_bits(void) {
    return (int)(sizeof(void *) * 8);
}

long mylinux_jdk_page_size(void) {
    return sysconf(_SC_PAGESIZE);
}

const char *mylinux_jdk_architecture(void) {
#if defined(__aarch64__)
    return "aarch64";
#elif defined(__arm__)
    return "arm";
#elif defined(__x86_64__)
    return "x86_64";
#elif defined(__i386__)
    return "i386";
#else
    return "unknown";
#endif
}
