# MyLinux Boot Control

Boot Control manages boot-slot information and boot-related device state.

Responsibilities:

- Query available boot slots
- Identify the active boot slot
- Report slot bootability
- Report successful boot state
- Request a slot change
- Track retry and failure information

The implementation must use the device's actual boot-control
interface rather than assuming that every device supports A/B slots.

This subsystem is under development.
