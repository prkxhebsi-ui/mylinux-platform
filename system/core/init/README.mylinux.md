# MyLinux Init Integration

This directory may contain MyLinux-specific init integration.

Rules:
- Preserve existing AOSP init sources.
- Do not start privileged services without an explicit design.
- Validate service configuration before enabling it.
- Integrate through the branch's supported build and init mechanisms.
- Keep MyLinux-specific code separately identifiable.
