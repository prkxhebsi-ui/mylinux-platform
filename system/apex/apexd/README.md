# MyLinux APEX daemon

Initial APEX management foundation.

Implemented:
- Daemon entry point
- Version reporting
- Command-line help
- System APEX directory scanner
- Data APEX directory scanner
- Regular-file filtering

Not implemented:
- APEX signature verification
- AVB/vbmeta verification
- APEX image decompression
- Loop-device creation
- Device-mapper integration
- Image mounting
- Binder APEX service
- Installation and rollback
- Persistent package database

This is a development scaffold, not a production APEX manager.
