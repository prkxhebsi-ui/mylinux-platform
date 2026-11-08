#ifndef MYLINUX_TYPES_H
#define MYLINUX_TYPES_H

#include <stdint.h>
#include <sys/types.h>

typedef uint8_t  sd_u8;
typedef uint16_t sd_u16;
typedef uint32_t sd_u32;
typedef uint64_t sd_u64;

typedef int32_t sd_i32;
typedef int64_t sd_i64;

typedef struct {
    pid_t pid;
    uid_t uid;
    gid_t gid;
} SDProcessIdentity;

typedef enum {
    SD_RESULT_OK = 0,
    SD_RESULT_ERROR = 1
} SDResult;

#endif
