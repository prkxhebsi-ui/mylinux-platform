# MyLinux init RC layout

Target: Android 11 / API 30

Core boot scripts:
- init.rc
- init.environ.rc
- init.recovery.rc
- init.usb.rc
- init.usb.configfs.rc
- init.zygote32.rc
- init.zygote64.rc
- init.zygote32_64.rc
- init.zygote64_32.rc

Component service scripts:
- system/apex/apexd/apexd.rc
- system/logging/logd/logd.rc
- system/netd/server/netd.rc
- frameworks/native/services/surfaceflinger/surfaceflinger.rc

Device configuration:
- device/mylinux/generic/init.mylinux.rc

This is a development scaffold, not a complete bootable Android init
configuration. Services must be built, installed, and configured with
matching SELinux policies before activation.
