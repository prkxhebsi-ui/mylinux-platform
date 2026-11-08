#include "compile_timer.h"

#include <errno.h>
#include <sys/time.h>

int compiler_time_now(struct compiler_time *result)
{
    struct timeval tv;

    if (result == 0) {
        errno = EINVAL;
        return -1;
    }

    if (gettimeofday(&tv, 0) != 0) {
        return -1;
    }

    result->seconds = (long)tv.tv_sec;
    result->microseconds = (long)tv.tv_usec;
    return 0;
}

long long compiler_time_elapsed_us(
    const struct compiler_time *start,
    const struct compiler_time *end)
{
    if (start == 0 || end == 0) {
        errno = EINVAL;
        return -1;
    }

    return ((long long)end->seconds - start->seconds) * 1000000LL +
           ((long long)end->microseconds - start->microseconds);
}
