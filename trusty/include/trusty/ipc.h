#ifndef MYLINUX_TRUSTY_IPC_H
#define MYLINUX_TRUSTY_IPC_H

#include <stdint.h>
#include <stddef.h>

#define TRUSTY_IPC_MAX_MESSAGE 4096

typedef struct {
    uint32_t command;
    uint32_t length;
    uint8_t data[TRUSTY_IPC_MAX_MESSAGE];
} trusty_ipc_message_t;

int trusty_ipc_validate(const trusty_ipc_message_t *message);

#endif
