/*
 * MyLinux AArch64 runtime syscall gateway.
 *
 * C interface:
 * long mylinux_arch_syscall6(
 *     long number,
 *     long arg0, long arg1, long arg2,
 *     long arg3, long arg4, long arg5
 * );
 *
 * AArch64 Linux syscall ABI:
 *   x8     = syscall number
 *   x0-x5  = syscall arguments
 *   x0     = return value
 */

#if defined(__aarch64__)

    .text
    .align  2

    .global mylinux_arch_syscall6
    .type mylinux_arch_syscall6, %function

mylinux_arch_syscall6:
    mov     x8, x0
    mov     x0, x1
    mov     x1, x2
    mov     x2, x3
    mov     x3, x4
    mov     x4, x5
    mov     x5, x6

    svc     #0
    ret

    .size mylinux_arch_syscall6, .-mylinux_arch_syscall6

/*
 * Runtime entry points.
 * The C implementations must be supplied by the runtime.
 */

    .global mylinux_runtime_boot_entry
    .type mylinux_runtime_boot_entry, %function

mylinux_runtime_boot_entry:
    b       mylinux_runtime_boot_main

    .global mylinux_runtime_root_entry
    .type mylinux_runtime_root_entry, %function

mylinux_runtime_root_entry:
    b       mylinux_runtime_root_main

#endif
