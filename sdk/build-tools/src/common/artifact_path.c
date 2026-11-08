#include <stddef.h>
#include <string.h>

int sdk_artifact_path_valid(const char *path)
{
    if (!path || path[0] == '\0' || path[0] == '/')
        return 0;

    const char *part = path;

    for (const char *p = path; ; ++p) {
        if (*p == '\\')
            return 0;

        if (*p == '/' || *p == '\0') {
            size_t length = (size_t)(p - part);

            if (length == 0)
                return 0;

            if (length == 2 && part[0] == '.' && part[1] == '.')
                return 0;

            if (*p == '\0')
                break;

            part = p + 1;
        }
    }

    return 1;
}
