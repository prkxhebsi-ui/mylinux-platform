#ifndef MYLINUX_SYS_TYPES_H
#define MYLINUX_SYS_TYPES_H

#ifndef __MYLINUX_SIZE_T_DEFINED
#define __MYLINUX_SIZE_T_DEFINED
typedef __SIZE_TYPE__ size_t;
#endif

#ifndef __MYLINUX_SSIZE_T_DEFINED
#define __MYLINUX_SSIZE_T_DEFINED
typedef __PTRDIFF_TYPE__ ssize_t;
#endif

typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;

typedef signed char int8_t;
typedef unsigned char uint8_t;
typedef signed short int16_t;
typedef unsigned short uint16_t;
typedef signed int int32_t;
typedef unsigned int uint32_t;
typedef signed long long int64_t;
typedef unsigned long long uint64_t;

typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef unsigned int mode_t;
typedef unsigned long dev_t;
typedef unsigned long ino_t;
typedef unsigned long nlink_t;
typedef long off_t;
typedef long blksize_t;
typedef long blkcnt_t;
typedef long time_t;
typedef long suseconds_t;
typedef int id_t;

#endif
