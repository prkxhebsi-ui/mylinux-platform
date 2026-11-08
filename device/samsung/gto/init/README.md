# MyLinux GTO Init Extensions

This directory holds device-specific Android init extension files.

Rules:
- Do not replace the platform init.rc.
- Do not import extensions until the import location is verified.
- Add services and triggers only for confirmed hardware requirements.
- Keep SELinux permissions and service ownership aligned with Android policy.
