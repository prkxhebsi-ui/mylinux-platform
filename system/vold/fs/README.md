# MyLinux vold filesystem detection

Files:
- include/vold_fs.h: filesystem detection interface.
- vold_fs.c: read-only signature inspection.

Supported detection:
- ext4: superblock magic.
- f2fs: superblock magic.
- vfat: conservative FAT boot-sector heuristic.

Limitations:
- Signature detection does not validate a complete filesystem.
- FAT identification is heuristic and may miss valid FAT volumes.
- No filesystem is mounted, formatted, repaired, or modified.
- Device discovery and mount policy belong to the volume manager.
- Unknown or unreadable input is reported as unknown.

This component is not, by itself, a complete vold implementation.
