# EVP Cipher API

## Initial cipher descriptors

- EVP_aes_128_cbc()
- EVP_aes_192_cbc()
- EVP_aes_256_cbc()

## Context operations

- EVP_CIPHER_CTX_new()
- EVP_CIPHER_CTX_free()
- EVP_CIPHER_CTX_reset()
- EVP_CIPHER_CTX_set_padding()

## Operation interfaces

- EVP_EncryptInit_ex()
- EVP_EncryptUpdate()
- EVP_EncryptFinal_ex()
- EVP_DecryptInit_ex()
- EVP_DecryptUpdate()
- EVP_DecryptFinal_ex()

## Status

Cipher metadata and context lifecycle are implemented.

Encryption and decryption intentionally fail until a reviewed AES backend,
padding implementation, and appropriate security tests are integrated.

This API is not yet a complete OpenSSL or BoringSSL ABI implementation.
