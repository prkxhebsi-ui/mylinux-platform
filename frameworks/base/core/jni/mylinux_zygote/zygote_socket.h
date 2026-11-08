#ifndef MYLINUX_ZYGOTE_SOCKET_H
#define MYLINUX_ZYGOTE_SOCKET_H

namespace mylinux {
namespace zygote {

int getInheritedServerSocket(const char* socketName);

} // namespace zygote
} // namespace mylinux

#endif
