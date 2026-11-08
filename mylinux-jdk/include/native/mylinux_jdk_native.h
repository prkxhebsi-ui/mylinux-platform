#ifndef MYLINUX_JDK_NATIVE_H
#define MYLINUX_JDK_NATIVE_H

#ifdef __cplusplus
extern "C" {
#endif

const char *mylinux_jdk_native_version(void);
int mylinux_jdk_pointer_bits(void);
long mylinux_jdk_page_size(void);
const char *mylinux_jdk_architecture(void);

#ifdef __cplusplus
}
#endif

#endif
