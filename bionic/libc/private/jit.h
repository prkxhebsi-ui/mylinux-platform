#ifndef MYLINUX_PRIVATE_JIT_H
#define MYLINUX_PRIVATE_JIT_H

/*
 * MyLinux private JIT interface.
 *
 * JIT memory management must follow the target OS security policy.
 * This header deliberately does not provide executable-memory
 * allocation or permission-changing implementations yet.
 */

typedef enum {
    MYLINUX_JIT_DISABLED = 0,
    MYLINUX_JIT_ENABLED = 1
} mylinux_jit_mode;

#endif
