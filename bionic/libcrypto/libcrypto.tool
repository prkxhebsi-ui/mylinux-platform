[tool]
name = libcrypto
kind = native-shared-library
language = c
standard = c11

[directories]
include = include
source = src
tests = tests

[build]
android_api = 30
architecture = aarch64
shared_library = true
remove_rpath_after_link = true

[compatibility]
openssl = true
boringssl = true

[security]
reviewed_crypto_backend = required
