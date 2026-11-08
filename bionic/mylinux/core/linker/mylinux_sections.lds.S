/*
 * MyLinux linker section fragment.
 * Preprocess this file before passing it to the linker.
 * It is not a complete standalone memory layout.
 */

#ifndef MYLINUX_SECTION_ALIGNMENT
#define MYLINUX_SECTION_ALIGNMENT 8
#endif

#ifndef MYLINUX_SECTION_KEEP
#define MYLINUX_SECTION_KEEP(section_name) KEEP(*(section_name))
#endif

SECTIONS
{
    .rodata.mylinux ALIGN(MYLINUX_SECTION_ALIGNMENT) :
    {
        __mylinux_rodata_start = .;
        KEEP(*(.rodata.mylinux))
        KEEP(*(.rodata.mylinux.*))
        __mylinux_rodata_end = .;
    }

    .data.mylinux ALIGN(MYLINUX_SECTION_ALIGNMENT) :
    {
        __mylinux_data_start = .;
        KEEP(*(.data.mylinux))
        KEEP(*(.data.mylinux.*))
        __mylinux_data_end = .;
    }

    .bss.mylinux ALIGN(MYLINUX_SECTION_ALIGNMENT) (NOLOAD) :
    {
        __mylinux_bss_start = .;
        KEEP(*(.bss.mylinux))
        KEEP(*(.bss.mylinux.*))
        __mylinux_bss_end = .;
    }

    .mylinux_metadata ALIGN(MYLINUX_SECTION_ALIGNMENT) :
    {
        __mylinux_metadata_start = .;
        KEEP(*(.mylinux.metadata))
        KEEP(*(.mylinux.metadata.*))
        __mylinux_metadata_end = .;
    }
}
INSERT AFTER .data;
