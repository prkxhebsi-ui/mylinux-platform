#include <trusty/ipc.h>

int trusty_ipc_validate(const trusty_ipc_message_t *message)
{
    if (!message)
        return -1;

    if (message->length > TRUSTY_IPC_MAX_MESSAGE)
        return -2;

    return 0;
}
