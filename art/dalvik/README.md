# MyLinux Dalvik Runtime

Dalvik is a register-based virtual machine designed to execute
Dalvik Executable (DEX) bytecode.

## Source layout

- vm/interpreter: DEX instruction interpreter
- vm/compiler: bytecode compilation components
- vm/analysis: bytecode and control-flow analysis
- vm/alloc: object and memory allocation
- vm/debugger: runtime debugging
- vm/gc: garbage collection
- vm/native: native method integration
- vm/oo: classes, objects and method dispatch
- vm/reflection: reflection implementation
- vm/jdwp: Java Debug Wire Protocol support
- libdex: DEX parsing and verification
- libdvm: Dalvik runtime library
- command: runtime command-line programs
- tools: development and inspection tools
- tests: runtime tests
- docs: architecture and implementation documentation

## Status

Initial source directory structure only.
No Dalvik runtime implementation or executable is included yet.
