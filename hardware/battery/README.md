# MyLinux Battery Framework

Two separate systems:

1. Terminal Battery:
   Software-only persistent percentage simulator.
   Command: charge <0-100>

2. Physical Battery API:
   C and C++ interfaces for developers implementing
   hardware-specific fuel-gauge drivers.

Supported configurations:
- 1S: one cell in series
- 2S: two cells in series
- 3S: three cells in series
- 4S: four cells in series

Supported source/header extensions:
.c .cpp .cxx .cc .h .hpp .hxx .hh

The common API reads and validates measurements.
It does not implement a charger, cell protection circuit,
cell balancing system, or hardware-specific gauge driver.

Hardware designs must use compatible fuel-gauge ICs,
independent protection, appropriate charging circuitry,
and validated cell-level limits.
