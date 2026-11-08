# libcrypto

MyLinux cryptographic library compatibility project.

## Compatibility goals

- OpenSSL-style public APIs.
- BoringSSL-style public APIs.
- Shared internal cryptographic implementation.
- Android/Bionic integration.
- Independent compatibility and regression tests.

## Security policy

Production cryptographic algorithms must use reviewed implementations.
Do not invent cryptographic primitives or use placeholder algorithms for
security-sensitive operations.

OpenSSL and BoringSSL have different API, ABI, and licensing requirements.
Compatibility must be implemented and tested explicitly.

## Current status

Initial public API declarations and build structure only.
No production cryptographic implementation is provided yet.
