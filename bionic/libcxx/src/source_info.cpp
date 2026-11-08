#include "mylinux_libcxx.hpp"

/* Integration marker; this is not an implementation of the C++ standard library. */
namespace mylinux {
namespace runtime {

const char* libcxx_source_status() noexcept {
    return "MyLinux libc++ integration pending";
}

} // namespace runtime
} // namespace mylinux
