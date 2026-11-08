#include <stddef.h>
#include <string.h>

int sdk_ndk_argument_safe(const char *argument)
{
    if (!argument || argument[0] == '\0')
        return 0;

    if (strstr(argument, "$(") || strstr(argument, "`") ||
        strstr(argument, "&&") || strstr(argument, "||") ||
        strstr(argument, ";") || strstr(argument, "|") ||
        strstr(argument, "\n") || strstr(argument, "\r"))
        return 0;

    return 1;
}
