#include "mylinux_dl_helpers.h"

#include <string.h>

int mydl_valid_library_name(const char *name)
{
    const unsigned char *cursor;

    if (name == NULL || name[0] == '\0')
        return 0;

    if (strstr(name, "..") != NULL)
        return 0;

    for (cursor = (const unsigned char *)name;
         *cursor != '\0'; ++cursor) {
        if (*cursor < 0x20 || *cursor == '/' || *cursor == '\\')
            return 0;
    }

    return 1;
}

int mydl_valid_symbol_name(const char *name)
{
    const unsigned char *cursor;

    if (name == NULL || name[0] == '\0')
        return 0;

    for (cursor = (const unsigned char *)name;
         *cursor != '\0'; ++cursor) {
        if (*cursor <= 0x20 || *cursor == '/' || *cursor == '\\')
            return 0;
    }

    return 1;
}

const char *mydl_basename(const char *path)
{
    const char *slash;
    const char *backslash;

    if (path == NULL)
        return NULL;

    slash = strrchr(path, '/');
    backslash = strrchr(path, '\\');

    if (slash == NULL)
        return backslash == NULL ? path : backslash + 1;

    if (backslash == NULL)
        return slash + 1;

    return slash > backslash ? slash + 1 : backslash + 1;
}

int mydl_has_shared_object_suffix(const char *name)
{
    size_t length;

    if (name == NULL)
        return 0;

    length = strlen(name);
    return length >= 3 &&
           strcmp(name + length - 3, ".so") == 0;
}

size_t mydl_copy_error(char *output, size_t capacity,
                       const char *message)
{
    size_t length;

    if (output == NULL || capacity == 0)
        return 0;

    if (message == NULL)
        message = "unknown dynamic-loader error";

    length = strlen(message);
    if (length >= capacity)
        length = capacity - 1;

    memcpy(output, message, length);
    output[length] = '\0';

    return length;
}
