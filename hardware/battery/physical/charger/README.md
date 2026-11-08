# MyLinux Charger Framework

Developer-oriented charger and power-input abstraction.

## Supported integration areas

- Legacy USB charging-port detection
- USB Type-C controller status
- USB Power Delivery contract reporting
- Cable identity and e-marker reporting
- Charger IC status and fault reporting
- Regulator status reporting
- Transistor/MOSFET power-switch status
- Current-sense resistor measurement
- Power-path status

## Cable clarification

Passive USB cables do not contain executable charging code.
Some USB-C cables contain an e-marker chip that reports cable
identity and electrical capabilities through the USB-C controller.

Legacy USB charging-port detection is performed by the device's
USB PHY or charging controller.

## Safety boundary

This framework does not provide generic direct control of
charging voltage, current, MOSFET gates, or battery charge enable.

Use a suitable charger IC, Type-C/PD controller, regulator,
power-path controller and independent battery protection.

All hardware-specific drivers must follow the exact chip datasheets
and be validated before connection to a real battery.

## Languages

C and C++.

Supported extensions:
.c .cpp .cxx .cc .h .hpp .hxx .hh
