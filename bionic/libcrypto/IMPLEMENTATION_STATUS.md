# Implementation Status

| Component | Status |
|---|---|
| Version information | Initial implementation |
| Error handling | Basic thread-local error |
| Secure random | getrandom() implementation |
| SHA-256 | Backend pending |
| SHA-512 | Backend pending |
| AES | Backend pending |
| HMAC | Backend pending |
| HKDF | Backend pending |
| OpenSSL compatibility | Partial declarations |
| BoringSSL compatibility | Partial declarations |

This project does not yet claim OpenSSL or BoringSSL ABI compatibility.

The random implementation requires Android/Linux getrandom support.
A failed random request returns failure; it never substitutes predictable
random data.

Production release requires cryptographic review, known-answer tests,
API compatibility tests, and build verification.
