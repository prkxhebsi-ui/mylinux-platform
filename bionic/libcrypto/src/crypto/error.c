#include <openssl/err.h>
#include "error_internal.h"

static _Thread_local unsigned long last_error;

void crypto_error_set(unsigned long error_code)
{
    last_error = error_code;
}

unsigned long ERR_get_error(void)
{
    unsigned long result = last_error;
    last_error = 0;
    return result;
}

unsigned long ERR_peek_error(void)
{
    return last_error;
}

void ERR_clear_error(void)
{
    last_error = 0;
}

void ERR_error_string_n(
    unsigned long error,
    char *buffer,
    unsigned long length)
{
    if (buffer == 0 || length == 0)
        return;

    buffer[0] = '\0';

    if (error != 0)
        buffer[0] = '?';

    if (length > 1 && error != 0)
        buffer[1] = '\0';
}
