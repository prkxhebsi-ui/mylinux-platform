/*
 * MyLinux AArch64 leaf helpers.
 * This is ordinary assembler input, not preprocessed assembly.
 */

.section .text.mylinux.helpers,"ax",%progbits
.p2align 2

.global mylinux_arm64_return_zero
.type mylinux_arm64_return_zero, %function
mylinux_arm64_return_zero:
    mov x0, #0
    ret
.size mylinux_arm64_return_zero, .-mylinux_arm64_return_zero

.global mylinux_arm64_return_one
.type mylinux_arm64_return_one, %function
mylinux_arm64_return_one:
    mov x0, #1
    ret
.size mylinux_arm64_return_one, .-mylinux_arm64_return_one

.global mylinux_arm64_return_version
.type mylinux_arm64_return_version, %function
mylinux_arm64_return_version:
    mov x0, #1
    ret
.size mylinux_arm64_return_version, .-mylinux_arm64_return_version

.global mylinux_arm64_is_zero
.type mylinux_arm64_is_zero, %function
mylinux_arm64_is_zero:
    cmp x0, #0
    cset w0, eq
    ret
.size mylinux_arm64_is_zero, .-mylinux_arm64_is_zero

.global mylinux_arm64_is_nonzero
.type mylinux_arm64_is_nonzero, %function
mylinux_arm64_is_nonzero:
    cmp x0, #0
    cset w0, ne
    ret
.size mylinux_arm64_is_nonzero, .-mylinux_arm64_is_nonzero

.global mylinux_arm64_min_u64
.type mylinux_arm64_min_u64, %function
mylinux_arm64_min_u64:
    cmp x0, x1
    csel x0, x0, x1, lo
    ret
.size mylinux_arm64_min_u64, .-mylinux_arm64_min_u64

.global mylinux_arm64_max_u64
.type mylinux_arm64_max_u64, %function
mylinux_arm64_max_u64:
    cmp x0, x1
    csel x0, x0, x1, hi
    ret
.size mylinux_arm64_max_u64, .-mylinux_arm64_max_u64

.global mylinux_arm64_clamp_u64
.type mylinux_arm64_clamp_u64, %function
mylinux_arm64_clamp_u64:
    cmp x0, x1
    csel x0, x0, x1, hs
    cmp x0, x2
    csel x0, x0, x2, ls
    ret
.size mylinux_arm64_clamp_u64, .-mylinux_arm64_clamp_u64

.global mylinux_arm64_align_down_16
.type mylinux_arm64_align_down_16, %function
mylinux_arm64_align_down_16:
    and x0, x0, #0xfffffffffffffff0
    ret
.size mylinux_arm64_align_down_16, .-mylinux_arm64_align_down_16

.global mylinux_arm64_align_up_16
.type mylinux_arm64_align_up_16, %function
mylinux_arm64_align_up_16:
    add x0, x0, #15
    and x0, x0, #0xfffffffffffffff0
    ret
.size mylinux_arm64_align_up_16, .-mylinux_arm64_align_up_16

.global mylinux_arm64_popcount_u64
.type mylinux_arm64_popcount_u64, %function
mylinux_arm64_popcount_u64:
    mov x1, #0
.Lpopcount_loop:
    cbz x0, .Lpopcount_done
    sub x2, x0, #1
    and x0, x0, x2
    add x1, x1, #1
    b .Lpopcount_loop
.Lpopcount_done:
    mov x0, x1
    ret
.size mylinux_arm64_popcount_u64, .-mylinux_arm64_popcount_u64

.global mylinux_arm64_test_bit
.type mylinux_arm64_test_bit, %function
mylinux_arm64_test_bit:
    cmp x1, #63
    b.hi .Lbit_invalid
    lsr x2, x0, x1
    and x0, x2, #1
    ret
.Lbit_invalid:
    mov x0, #0
    ret
.size mylinux_arm64_test_bit, .-mylinux_arm64_test_bit

.global mylinux_arm64_byte_swap_32
.type mylinux_arm64_byte_swap_32, %function
mylinux_arm64_byte_swap_32:
    rev w0, w0
    ret
.size mylinux_arm64_byte_swap_32, .-mylinux_arm64_byte_swap_32

.global mylinux_arm64_byte_swap_64
.type mylinux_arm64_byte_swap_64, %function
mylinux_arm64_byte_swap_64:
    rev x0, x0
    ret
.size mylinux_arm64_byte_swap_64, .-mylinux_arm64_byte_swap_64

.global mylinux_arm64_count_leading_zeroes
.type mylinux_arm64_count_leading_zeroes, %function
mylinux_arm64_count_leading_zeroes:
    clz x0, x0
    ret
.size mylinux_arm64_count_leading_zeroes, .-mylinux_arm64_count_leading_zeroes

.global mylinux_arm64_count_trailing_zeroes
.type mylinux_arm64_count_trailing_zeroes, %function
mylinux_arm64_count_trailing_zeroes:
    rbit x0, x0
    clz x0, x0
    ret
.size mylinux_arm64_count_trailing_zeroes, .-mylinux_arm64_count_trailing_zeroes

.section .note.GNU-stack,"",%progbits
