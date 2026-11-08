# MyLinux Dalvik Java Support

Java-side support library for MyLinux Dalvik.

## Source

src/main/java/
    org/mylinux/dalvik/config/
        RuntimeConfig.java
        ToolDescriptor.java

## Resources

src/main/resources/config/
    runtime.conf
    runtime.json

src/main/resources/tools/
    dex-inspector.tool

## Configuration readers

RuntimeConfig:
- Reads runtime.conf
- Reads runtime.json
- Exposes runtime settings and metadata

ToolDescriptor:
- Reads .tool descriptors
- Validates tool ID and executable path
- Exposes tool metadata

## Current status

Implemented:
- Properties configuration reader
- JSON metadata reader
- Tool descriptor reader

Not implemented:
- Dalvik VM
- DEX execution
- Native tool execution
- Dynamic class loading
