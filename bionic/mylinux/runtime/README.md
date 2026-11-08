# MyLinux Runtime Core

Library identity:
    libmylinux

Architecture target:
    AArch64 Linux/Android

Runtime components:

- runtime.c: runtime state and feature registry
- cstring.c: string and memory utilities
- iostream.c: file-descriptor stream interface
- format.c: formatted output
- runtime_entry.c: boot and root entry hooks
- core_syscall.S: AArch64 syscall gateway
- core_logic.S.lds.S: preprocessed linker section layout
- syscall_policy.c: syscall policy descriptors

Security design:

- Mount operations are restricted.
- Unmount operations are restricted.
- File-descriptor inspection is restricted.
- Sysfs access is restricted.
- Path restrictions require kernel-enforced access control.

Metadata:

- ART-inspired runtime metadata
- MyLinux symbol records
- MyLinux feature records
- Runtime section descriptors
- Security policy descriptors

Status:

Prototype implementation. Not yet a production runtime.
No build or execution is authorized by this source definition alone.
