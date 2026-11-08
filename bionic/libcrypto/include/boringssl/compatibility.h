#ifndef MYLIBCRYPTO_BORINGSSL_COMPATIBILITY_H
#define MYLIBCRYPTO_BORINGSSL_COMPATIBILITY_H

/*
 * MyLinux BoringSSL compatibility entry point.
 *
 * Additional BoringSSL-compatible declarations will be added here.
 * This header does not claim complete BoringSSL API or ABI compatibility.
 */

#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/rand.h>

#endif
