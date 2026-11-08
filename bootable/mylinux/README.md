# MyLinux Bootable

The bootable source tree contains components involved in starting,
maintaining, and recovering the MyLinux operating system.

## Components

- bootimg: boot image inspection and parsing
- recovery: standalone recovery environment
- bootcontrol: boot-slot and boot-state management
- common: shared boot utilities

## Design

Boot components must remain independent of the normal Android
application framework wherever possible.

Hardware-specific bootloader operations belong in device integration
layers, not in generic boot-image parsing code.

All destructive operations require explicit authorization.

## Status

The initial source structure and boot-image magic checker are present.
Full boot-image parsing, recovery implementation, and boot-control
integration remain under development.
