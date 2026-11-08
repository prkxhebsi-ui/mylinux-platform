#ifndef MYLINUX_SYS_MMAN_H
#define MYLINUX_SYS_MMAN_H

#ifndef __MYLINUX_SIZE_T_DEFINED
#define __MYLINUX_SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

typedef long long mylinux_mmap_offset_t;

#define PROT_NONE  0x0
#define PROT_READ  0x1
#define PROT_WRITE 0x2
#define PROT_EXEC  0x4

#define MAP_SHARED     0x01
#define MAP_PRIVATE    0x02
#define MAP_FIXED      0x10
#define MAP_ANONYMOUS  0x20
#define MAP_ANON MAP_ANONYMOUS
#define MAP_GROWSDOWN  0x0100
#define MAP_DENYWRITE  0x0800
#define MAP_EXECUTABLE 0x1000
#define MAP_LOCKED     0x2000
#define MAP_NORESERVE  0x4000
#define MAP_POPULATE   0x8000
#define MAP_STACK      0x20000
#define MAP_HUGETLB    0x40000

#define MS_ASYNC      1
#define MS_INVALIDATE 2
#define MS_SYNC       4

#define MCL_CURRENT 1
#define MCL_FUTURE  2

#define MADV_NORMAL     0
#define MADV_RANDOM     1
#define MADV_SEQUENTIAL 2
#define MADV_WILLNEED   3
#define MADV_DONTNEED   4
#define MADV_FREE       8

#define MAP_FAILED ((void *)-1)

#ifdef __cplusplus
extern "C" {
#endif

void *mmap(void *address, size_t length,
           int protection, int flags,
           int fd, mylinux_mmap_offset_t offset);

int munmap(void *address, size_t length);

int mprotect(void *address, size_t length, int protection);

int msync(void *address, size_t length, int flags);

int mlock(const void *address, size_t length);
int munlock(const void *address, size_t length);
int mlockall(int flags);
int munlockall(void);

int madvise(void *address, size_t length, int advice);

#ifdef __cplusplus
}
#endif

#endif
