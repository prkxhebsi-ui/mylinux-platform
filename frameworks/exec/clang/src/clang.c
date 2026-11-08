#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * MyLinux Clang launcher.
 *
 * This launcher delegates to a real installed Clang compiler.
 * It is not the LLVM/Clang compiler implementation itself.
 */

int main(int argc, char **argv) {
    const char *compiler = getenv("MYLINUX_REAL_CLANG");

    (void)argc;

    if (!compiler || !*compiler)
        compiler = "/data/data/com.termux/files/usr/bin/clang";

    argv[0] = (char *)compiler;
    execv(compiler, argv);

    perror("mylinux-clang: execv");
    return 127;
}
