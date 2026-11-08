#include <errno.h>
#include <stddef.h>
#include <sys/random.h>
#include <openssl/rand.h>

int RAND_bytes(unsigned char *buffer, int length)
{
    size_t offset = 0;

    if (length < 0 || (length > 0 && buffer == NULL))
        return 0;

    while (offset < (size_t)length) {
        ssize_t result = getrandom(
            buffer + offset,
            (size_t)length - offset,
            0
        );

        if (result > 0) {
            offset += (size_t)result;
            continue;
        }

        if (result < 0 && errno == EINTR)
            continue;

        return 0;
    }

    return 1;
}

int RAND_priv_bytes(unsigned char *buffer, int length)
{
    return RAND_bytes(buffer, length);
}
