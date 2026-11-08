# Framework Command Sources

Standalone C command implementations.

| Source | Responsibility |
|---|---|
| uname.c | Kernel and system identification |
| uptime.c | System uptime and idle time |
| id.c | Current user and group identity |
| mounts.c | Current process mount table |

## Implementation

- C language
- POSIX/Linux system interfaces
- No MyLinux-prefixed source filenames
- No execution during source creation

## Build

Each source is intended to become an independent executable.
Build definitions will be added separately.
