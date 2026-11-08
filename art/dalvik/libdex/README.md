# MyLinux libdex

DEX file parsing library for the Dalvik runtime.

## Implemented

- DEX file loading from disk
- DEX file loading from memory
- DEX magic validation
- Header parsing
- File-size validation
- Endian validation
- DEX table boundary checks
- String ID lookup
- ULEB128 string-length decoding
- Error reporting

## Build

Run:

    ./build/build-libdex.sh

Output:

    ../../../../prebuilts/lib/libdex.so

## Limitations

This is an initial parser, not a complete DEX verifier.

It does not yet:
- Verify the SHA-1 signature or Adler-32 checksum
- Parse every DEX map item
- Decode class definitions and method code
- Validate all string encodings
- Support reverse-endian DEX files
