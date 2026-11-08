MyLinux VoIP Extensions

Package:
  org.mylinux.voip.wlan
  org.mylinux.voip.network

Features:
  - WLAN interface information
  - RSSI-like readings in dBm
  - Wireless link quality
  - Wireless noise readings
  - Interface operating state
  - Carrier state
  - MAC address
  - Basic signal-strength classification

Kernel relationship:
  wlan.ko is the WLAN kernel driver.
  Java helpers read information exposed through Linux procfs/sysfs.

Limitations:
  - /proc/net/wireless may not be exposed by every driver.
  - RSSI may be unavailable.
  - RSSI alone cannot determine VoIP call quality.
  - No packet transmission or WLAN driver control is implemented.
  - No microphone, audio codec, SIP, or WebRTC implementation
    is included in this library.
