#ifndef MYLINUX_SOCKET_PLATFORM_H
#define MYLINUX_SOCKET_PLATFORM_H

/* Standard C headers */
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>

/* Standard C++ headers */
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <climits>
#include <cstring>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <new>

/* POSIX and Linux/Android headers */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

/* Optional platform headers */
#if defined(__has_include)

#if __has_include(<sys/auxv.h>)
#include <sys/auxv.h>
#define MYLINUX_HAVE_AUXV 1
#else
#define MYLINUX_HAVE_AUXV 0
#endif

#if __has_include(<sys/epoll.h>)
#include <sys/epoll.h>
#define MYLINUX_HAVE_EPOLL 1
#else
#define MYLINUX_HAVE_EPOLL 0
#endif

#if __has_include(<jni.h>)
#include <jni.h>
#define MYLINUX_HAVE_JNI 1
#else
#define MYLINUX_HAVE_JNI 0
#endif

#else
#define MYLINUX_HAVE_AUXV 0
#define MYLINUX_HAVE_EPOLL 0
#define MYLINUX_HAVE_JNI 0
#endif

#endif
