#ifndef MYLINUX_POLL_H
#define MYLINUX_POLL_H

#ifndef __MYLINUX_SIZE_T_DEFINED
#define __MYLINUX_SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

typedef unsigned long nfds_t;

struct pollfd {
    int fd;
    short events;
    short revents;
};

#define POLLIN      0x0001
#define POLLPRI     0x0002
#define POLLOUT     0x0004
#define POLLERR     0x0008
#define POLLHUP     0x0010
#define POLLNVAL    0x0020
#define POLLRDNORM  0x0040
#define POLLRDBAND  0x0080
#define POLLWRNORM  0x0100
#define POLLWRBAND  0x0200
#define POLLMSG     0x0400

#ifdef __cplusplus
extern "C" {
#endif

int poll(struct pollfd *fds, nfds_t count, int timeout);
int ppoll(struct pollfd *fds, nfds_t count,
          const void *timeout, const void *signal_mask);

#ifdef __cplusplus
}
#endif

#endif
