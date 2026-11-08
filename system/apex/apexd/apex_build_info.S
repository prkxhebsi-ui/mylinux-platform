#define APEX_ARCH_BITS 64

.section .rodata
.align 3
.global apex_build_label
.type apex_build_label, %object

apex_build_label:
    .asciz "MyLinux APEX ARM64"

.size apex_build_label, .-apex_build_label

.text
.align 2
.global apex_assembly_bits
.type apex_assembly_bits, %function

apex_assembly_bits:
    mov x0, #APEX_ARCH_BITS
    ret

.size apex_assembly_bits, .-apex_assembly_bits
