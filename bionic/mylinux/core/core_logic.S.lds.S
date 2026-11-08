#define MYLINUX_ALIGN 8

SECTIONS
{
    .rodata.mylinux : ALIGN(MYLINUX_ALIGN)
    {
        __mylinux_rodata_start = .;

        KEEP(*(.rodata.mylinux.*))
        KEEP(*(.mylinux.metadata))
        KEEP(*(.mylinux.syscalls))
        KEEP(*(.mylinux.boot))

        __mylinux_rodata_end = .;
    }

    .data.mylinux : ALIGN(MYLINUX_ALIGN)
    {
        __mylinux_data_start = .;
        KEEP(*(.data.mylinux.*))
        __mylinux_data_end = .;
    }

    .mylinux_runtime : ALIGN(MYLINUX_ALIGN)
    {
        __mylinux_runtime_start = .;
        KEEP(*(.mylinux.runtime.*))
        __mylinux_runtime_end = .;
    }

    .mylinux_security : ALIGN(MYLINUX_ALIGN)
    {
        __mylinux_security_start = .;
        KEEP(*(.rodata.mylinux.security))
        __mylinux_security_end = .;
    }
}
INSERT AFTER .rodata;
