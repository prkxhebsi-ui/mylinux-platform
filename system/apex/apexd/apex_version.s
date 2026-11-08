.section .text
.align 2

.global apex_assembly_version
.type apex_assembly_version, %function

apex_assembly_version:
    mov x0, #11
    ret

.size apex_assembly_version, .-apex_assembly_version
