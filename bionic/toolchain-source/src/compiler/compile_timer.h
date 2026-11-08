#ifndef MYLINUX_COMPILE_TIMER_H
#define MYLINUX_COMPILE_TIMER_H

struct compiler_time {
    long seconds;
    long microseconds;
};

int compiler_time_now(struct compiler_time *result);
long long compiler_time_elapsed_us(
    const struct compiler_time *start,
    const struct compiler_time *end);

#endif
