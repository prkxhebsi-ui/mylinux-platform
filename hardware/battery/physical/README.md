# MyLinux Physical Battery API

This directory contains the physical battery software framework.

It is separate from the terminal battery simulator.

## Main components

- core/: battery manager, monitoring, estimation and diagnostics
- machinery/: sensing and hardware subsystem integration points
- interfaces/: C and C++ developer interfaces
- transports/: I2C and SPI transport starting points
- templates/editable/: developer-editable templates
- templates/reference/: canonical read-only reference templates
- profiles/: 1S, 2S, 3S and 4S software profiles
- board/: hardware design documentation areas
- tests/: developer test sources

## Languages

C and C++.

Supported extensions:
.c .cpp .cxx .cc .h .hpp .hxx .hh

## Important

Most machinery files are unimplemented integration points.
They do not operate real hardware yet.

The framework does not implement cell charging, cell balancing,
or independent electrical protection.

All real battery designs require appropriate cell specifications,
independent protection, validated charger compatibility,
thermal design, and hardware testing.
