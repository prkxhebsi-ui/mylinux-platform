#ifndef MYLINUX_EPOLL_H
#define MYLINUX_EPOLL_H
typedef union mylinux_epoll_data {
    void *ptr;
    int fd;
    unsigned int u32;
    unsigned long long u64;
} mylinux_epoll_data_t;
struct mylinux_epoll_event {
    unsigned int events;
    mylinux_epoll_data_t data;
} __attribute__((packed));
#endif
