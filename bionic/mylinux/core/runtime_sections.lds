/* Example linker fragment; not a complete standalone linker script. */
SECTIONS
{
    .rodata.mylinux :
    {
        KEEP(*(.rodata.mylinux))
        KEEP(*(.rodata.mylinux.*))
    }

    .data.mylinux :
    {
        KEEP(*(.data.mylinux))
        KEEP(*(.data.mylinux.*))
    }
}
INSERT AFTER .data;
