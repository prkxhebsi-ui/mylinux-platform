# EVP MAC and KDF APIs

## MAC
- EVP_MAC_fetch
- EVP_MAC_CTX_new
- EVP_MAC_CTX_free
- EVP_MAC_init
- EVP_MAC_update
- EVP_MAC_final

## KDF
- EVP_KDF_fetch
- EVP_KDF_CTX_new
- EVP_KDF_CTX_free
- EVP_KDF_derive

## Initial algorithms
- HMAC
- HKDF

## Status
Descriptor lookup and context lifecycle are implemented.
MAC and KDF operations require a reviewed cryptographic backend.

No placeholder cryptographic output is generated.
