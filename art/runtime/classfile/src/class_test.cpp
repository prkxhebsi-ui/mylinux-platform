#include "mylinux/classfile/ClassFile.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        puts("Usage: class_test file.class");
        return 1;
    }

    mylinux::art::ClassFile class_file;

    if (!mylinux::art::ClassReader::read(
            argv[1],
            &class_file)) {
        return 1;
    }

    puts("MyLinux ART class reader initialized");
    return 0;
}
