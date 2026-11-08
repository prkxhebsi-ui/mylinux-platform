/*
 * MyLinux ARM64 runtime markers.
 * Preprocessed assembly source; not a boot entry point.
 */

#ifndef MYLINUX_ASM_VERSION
#define MYLINUX_ASM_VERSION 1
#endif

#ifndef MYLINUX_ASM_SYMBOL
#define MYLINUX_ASM_SYMBOL(name) mylinux_##name
#endif

.section .rodata.mylinux.asm_metadata,"a",%progbits
.p2align 3

.global mylinux_asm_metadata_version
.type mylinux_asm_metadata_version, %object
mylinux_asm_metadata_version:
    .quad MYLINUX_ASM_VERSION
.size mylinux_asm_metadata_version, .-mylinux_asm_metadata_version

.global mylinux_asm_architecture
.type mylinux_asm_architecture, %object
mylinux_asm_architecture:
    .asciz "aarch64"
.size mylinux_asm_architecture, .-mylinux_asm_architecture

.global mylinux_asm_component
.type mylinux_asm_component, %object
mylinux_asm_component:
    .asciz "bionic-mylinux"
.size mylinux_asm_component, .-mylinux_asm_component

.section .rodata.mylinux.asm_strings,"a",%progbits
.p2align 3

.global mylinux_asm_status_ready
.type mylinux_asm_status_ready, %object
mylinux_asm_status_ready:
    .asciz "source-available"
.size mylinux_asm_status_ready, .-mylinux_asm_status_ready

.global mylinux_asm_status_unavailable
.type mylinux_asm_status_unavailable, %object
mylinux_asm_status_unavailable:
    .asciz "unavailable"
.size mylinux_asm_status_unavailable, .-mylinux_asm_status_unavailable

.global mylinux_asm_status_uninitialized
.type mylinux_asm_status_uninitialized, %object
mylinux_asm_status_uninitialized:
    .asciz "uninitialized"
.size mylinux_asm_status_uninitialized, .-mylinux_asm_status_uninitialized

.section .rodata.mylinux.asm_features,"a",%progbits
.p2align 3

.global mylinux_asm_feature_count
.type mylinux_asm_feature_count, %object
mylinux_asm_feature_count:
    .quad 16
.size mylinux_asm_feature_count, .-mylinux_asm_feature_count

.global mylinux_asm_feature_names
.type mylinux_asm_feature_names, %object
mylinux_asm_feature_names:
    .asciz "runtime"
    .asciz "metadata"
    .asciz "diagnostics"
    .asciz "symbols"
    .asciz "linker"
    .asciz "assembly"
    .asciz "memory"
    .asciz "threading"
    .asciz "logging"
    .asciz "validation"
    .asciz "compatibility"
    .asciz "testing"
    .asciz "configuration"
    .asciz "instrumentation"
    .asciz "profiling"
    .asciz "integration"
.size mylinux_asm_feature_names, .-mylinux_asm_feature_names

.section .data.mylinux.asm_state,"aw",%progbits
.p2align 3

.global mylinux_asm_state_version
.type mylinux_asm_state_version, %object
mylinux_asm_state_version:
    .quad MYLINUX_ASM_VERSION
.size mylinux_asm_state_version, .-mylinux_asm_state_version

.global mylinux_asm_state_flags
.type mylinux_asm_state_flags, %object
mylinux_asm_state_flags:
    .quad 0
.size mylinux_asm_state_flags, .-mylinux_asm_state_flags

.section .note.GNU-stack,"",%progbits
