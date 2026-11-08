MYLINUX PLATFORM METADATA
=========================

Purpose
-------
This directory contains source-controlled metadata describing the
MyLinux native platform and its interfaces.

The metadata table is not a source of device identity or security
authorization. It contains static descriptive values.

Source organization
-------------------
platform_metadata.c implements the metadata lookup interface.
The public declaration belongs in the MyLinux include directory.
Platform-specific generated values should be supplied by the build
system rather than silently inferred from the running device.

Lookup rules
------------
Keys are case-sensitive.
Keys are NUL-terminated C strings.
A NULL key is invalid and returns no value.
Unknown keys return NULL.
Returned values have static storage duration.
Callers must not free returned values.
Callers must not modify returned values.
The metadata table is immutable after startup.

Threading
---------
Read-only lookup does not mutate shared state.
No initialization routine is required for the static table.
No allocation is required for ordinary lookup.
The caller remains responsible for passing a valid readable string.

Versioning
----------
The interface has an explicit version.
Changes to key names should be reviewed for compatibility.
Removing an existing key can break callers.
Adding a key should not change the meaning of existing keys.
Generated metadata should record the source revision separately.

Security
--------
Metadata does not grant privileges.
Metadata does not enforce SELinux policy.
Metadata does not bypass Android partition boundaries.
Metadata does not establish verified boot status.
Metadata does not replace kernel syscall enforcement.
Metadata must not contain passwords or private signing keys.
Diagnostic output must not expose sensitive process data.

Build integration
-----------------
The implementation must be compiled by an explicit build target.
The public header must be included by consumers.
The source must not be added to an upstream target blindly.
AOSP build definitions vary by release and target.
MyLinux integration should use a dedicated module definition.
Warnings should be enabled for native compilation.
Tests should cover missing keys and known values.

Testing recommendations
-----------------------
Check the metadata version.
Check that the entry count is nonzero.
Check known keys for exact values.
Check an unknown key.
Check a NULL key.
Check case-sensitive lookup.
Check that returned strings are stable.
Check duplicate keys during review.
Check generated configuration against the target product.
Check that release builds do not use development defaults.

Maintenance
-----------
Review every key before changing its meaning.
Document the owner of generated values.
Avoid claiming runtime health from static metadata.
Avoid claiming security enforcement from configuration.
Keep this file synchronized with the public header.
Keep test expectations synchronized with approved metadata.
Use source control to review all changes.

Status
------
This is a development implementation.
It is not a complete AOSP metadata service.
It has not been compiled or tested in this batch.
It is not ready for production integration.
