#ifndef MYLINUX_CLASSFILE_H
#define MYLINUX_CLASSFILE_H

#include <cassert>
#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#define MYLINUX_CLASS_MAGIC 0xCAFEBABE

namespace mylinux {
namespace art {

typedef unsigned char u1;
typedef unsigned short u2;
typedef unsigned int u4;

struct ClassHeader {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
};

struct ConstantPoolEntry {
    u1 tag;
    u4 value;
    std::string text;
};

struct ClassFile {
    ClassHeader header;
    std::vector<ConstantPoolEntry> constant_pool;
    std::string source_file;
};

class ClassReader {
public:
    static int read(
        const char* filename,
        ClassFile* class_file
    );

private:
    static int read_u1(FILE* file, u1* value);
    static int read_u2(FILE* file, u2* value);
    static int read_u4(FILE* file, u4* value);
};

}
}

#endif
