# MyLinux Physical Battery Developer Guide

1. Choose a supported topology: 1S, 2S, 3S or 4S.
2. Select a compatible fuel-gauge IC.
3. Read the exact IC datasheet and reference design.
4. Implement a gauge driver in C or C++.
5. Implement the correct I2C or SPI transport.
6. Add voltage, current and temperature measurements.
7. Integrate independent protection status reporting.
8. Validate measurements and fault behavior.
9. Add tests for disconnected and invalid hardware.
10. Review the complete electrical design before connecting cells.

Do not treat software validation as electrical protection.
Do not use a generic profile as a charger configuration.
