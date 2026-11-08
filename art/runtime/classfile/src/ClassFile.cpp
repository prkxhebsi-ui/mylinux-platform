#include "mylinux/classfile/ClassFile.h"

namespace mylinux {
namespace art {

int ClassReader::read_u1(FILE* file, u1* value) {
    int result = fgetc(file);

    if (result == EOF) {
        return 0;
    }

    *value = (u1)result;
    return 1;
}

int ClassReader::read_u2(FILE* file, u2* value) {
    u1 bytes[2];

    if (!read_u1(file, &bytes[0])) return 0;
    if (!read_u1(file, &bytes[1])) return 0;

    *value = ((u2)bytes[0] << 8) |
             ((u2)bytes[1]);

    return 1;
}

int ClassReader::read_u4(FILE* file, u4* value) {
    u1 bytes[4];

    if (!read_u1(file, &bytes[0])) return 0;
    if (!read_u1(file, &bytes[1])) return 0;
    if (!read_u1(file, &bytes[2])) return 0;
    if (!read_u1(file, &bytes[3])) return 0;

    *value = ((u4)bytes[0] << 24) |
             ((u4)bytes[1] << 16) |
             ((u4)bytes[2] << 8) |
             ((u4)bytes[3]);

    return 1;
}

int ClassReader::read(
    const char* filename,
    ClassFile* class_file
) {
    assert(filename != nullptr);
    assert(class_file != nullptr);

    FILE* file = fopen(filename, "rb");

    if (file == nullptr) {
        puts("ART: cannot open class file");
        return 0;
    }

    ClassHeader header = {};

    int valid =
        read_u4(file, &header.magic) &&
        read_u2(file, &header.minor_version) &&
        read_u2(file, &header.major_version) &&
        read_u2(file, &header.constant_pool_count);

    if (!valid) {
        puts("ART: truncated class header");
        fclose(file);
        return 0;
    }

    if (header.magic != MYLINUX_CLASS_MAGIC) {
        puts("ART: invalid class file magic");
        fclose(file);
        return 0;
    }

    if (header.major_version < 45 ||
        header.major_version > 52) {
        puts("ART: unsupported class version");
        fclose(file);
        return 0;
    }

    if (header.constant_pool_count == 0 ||
        header.constant_pool_count > 65535) {
        puts("ART: invalid constant pool count");
        fclose(file);
        return 0;
    }

    class_file->header = header;
    class_file->constant_pool.clear();
    class_file->constant_pool.resize(
        header.constant_pool_count
    );

    puts("ART: valid Java class header");
    puts("ART: class file loaded");

    fclose(file);
    return 1;
}

}
}
