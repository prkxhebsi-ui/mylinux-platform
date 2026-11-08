# Parameter API foundation

This directory documents the initial MyLinux parameter API layer.

Implemented foundations:
- OSSL_PARAM typed entries and terminator.
- Parameter lookup and basic typed get/set operations.
- OSSL_PARAM_BLD allocation and parameter-array construction.
- OSSL_LIB_CTX allocation and global-default placeholder.

Limitations:
- This is a partial API foundation, not OpenSSL ABI compatibility.
- Parameter arrays returned by OSSL_PARAM_BLD_to_param() own their
  duplicated keys and data; callers must free each allocation and the array.
- OSSL_LIB_CTX_set0_default() is not implemented yet and returns NULL.
- Provider loading, thread-local default contexts, type conversion,
  and complete OpenSSL parameter semantics remain future work.
- Do not use this layer for production cryptographic operations.
