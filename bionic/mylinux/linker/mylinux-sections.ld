SECTIONS
{
    .rodata.mylinux : ALIGN(8)
    {
        __mylinux_rodata_start = .;

        KEEP(*(.rodata.mylinux.*))
        KEEP(*(.mylinux.syscalls))
        KEEP(*(.mylinux.boot))

        __mylinux_rodata_end = .;
    }

    .data.mylinux : ALIGN(8)
    {
        __mylinux_data_start = .;

        KEEP(*(.data.mylinux.*))

        __mylinux_data_end = .;
    }

    .mylinux_metadata : ALIGN(8)
    {
        __mylinux_metadata_start = .;
        KEEP(*(.mylinux.metadata))
        __mylinux_metadata_end = .;
    }
}
INSERT AFTER .rodata;
