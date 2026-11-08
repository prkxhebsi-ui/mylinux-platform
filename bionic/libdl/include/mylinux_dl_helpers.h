#ifndef MYLINUX_DL_HELPERS_H
#define MYLINUX_DL_HELPERS_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int mydl_valid_library_name(const char *name);
int mydl_valid_symbol_name(const char *name);
const char *mydl_basename(const char *path);
int mydl_has_shared_object_suffix(const char *name);
size_t mydl_copy_error(char *output, size_t capacity,
                       const char *message);

#ifdef __cplusplus
}
#endif

#endif
