#ifndef MYLINUX_COMPILER_FD_H
#define MYLINUX_COMPILER_FD_H

int compiler_open_readonly(const char *path);
int compiler_set_cloexec(int fd);
int compiler_close_fd(int fd);

#endif
