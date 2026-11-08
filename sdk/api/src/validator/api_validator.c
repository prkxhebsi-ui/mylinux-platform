#include <stddef.h>
#include <string.h>

int mylinux_sdk_api_name_valid(const char *name)
{
    if (name == NULL || name[0] == '\0')
        return 0;

    if (!(name[0] == '_' ||
          (name[0] >= 'A' && name[0] <= 'Z') ||
          (name[0] >= 'a' && name[0] <= 'z')))
        return 0;

    for (size_t i = 1; name[i] != '\0'; ++i) {
        char c = name[i];

        if (!(c == '_' || c == '.' || c == '-' ||
              (c >= 'A' && c <= 'Z') ||
              (c >= 'a' && c <= 'z') ||
              (c >= '0' && c <= '9')))
            return 0;
    }

    return 1;
}
