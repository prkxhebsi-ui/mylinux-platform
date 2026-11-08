# MyLinux vold

Storage and volume management daemon.

Target:
- Android 11
- API 30
- ARM64

Responsibilities:
- Block-device discovery
- Partition inspection
- Filesystem detection
- Volume mounting and unmounting
- Public storage management
- Private storage management
- Emulated shared storage
- Encryption management
- Device event monitoring

Primary shared-storage path:

/storage/self/primary

Compatibility alias:

/sdcard -> /storage/self/primary

Security requirements:
- Do not mount untrusted filesystems without validation.
- Do not expose private application storage.
- Validate mount options.
- Do not format disks automatically.
- Do not execute arbitrary commands from device metadata.

This is a custom MyLinux implementation, not the official
Android vold source.
