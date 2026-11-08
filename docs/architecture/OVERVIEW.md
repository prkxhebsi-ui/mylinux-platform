# MyLinux Architecture Overview

## Main layers

### 1. Hardware layer
Hardware interfaces, hardware abstraction libraries, and vendor
implementations.

### 2. Core system
Initialization, filesystem management, logging, properties,
process management, and system services.

### 3. Runtime and framework
Runtime support, framework APIs, and platform services.

### 4. Applications
System packages and user-facing applications.

### 5. Security
Access control, permissions, and SELinux policy.

## Development principle

Keep components modular. Document dependencies and interfaces.
Avoid claiming compatibility until it has been tested.

## Current architecture status

This document describes the intended architecture, not a claim
that every layer is implemented.
