/*
 * MyLinux data-section linker fragment.
 * Intended for integration into a compatible ELF linker script.
 */

SECTIONS
{
    .rodata.mylinux :
    {
        __mylinux_constants_begin = .;
        KEEP(*(.rodata.mylinux))
        KEEP(*(.rodata.mylinux.*))
        __mylinux_constants_end = .;
    }

    .data.mylinux :
    {
        __mylinux_initialized_begin = .;
        KEEP(*(.data.mylinux))
        KEEP(*(.data.mylinux.*))
        __mylinux_initialized_end = .;
    }

    .bss.mylinux (NOLOAD) :
    {
        __mylinux_zero_initialized_begin = .;
        KEEP(*(.bss.mylinux))
        KEEP(*(.bss.mylinux.*))
        __mylinux_zero_initialized_end = .;
    }

    .mylinux_metadata :
    {
        __mylinux_metadata_begin = .;
        KEEP(*(.mylinux.metadata))
        KEEP(*(.mylinux.metadata.*))
        __mylinux_metadata_end = .;
    }
}
INSERT AFTER .data;
