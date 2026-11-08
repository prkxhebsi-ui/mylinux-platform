# EVP API

The EVP interface provides a high-level cryptographic API.

## Initial support

- SHA-256 descriptor metadata
- SHA-512 descriptor metadata
- Digest context allocation
- Digest context reset and cleanup
- Digest size queries

## Pending

- Digest initialization backend
- Digest update backend
- Digest finalization backend
- Cipher contexts
- Encrypt/decrypt operations
- OpenSSL ABI compatibility
- BoringSSL-specific compatibility

Digest operations currently return failure intentionally.
