#include <stddef.h>
#include <string.h>

int mylinux_string_selftest(void)
{
    char text[16] = "MyLinux";
    char overlap[8] = "abcdef";

    if (strlen(text) != 7)
        return 1;

    if (strcmp(text, "MyLinux") != 0)
        return 2;

    if (strncmp(text, "My", 2) != 0)
        return 3;

    if (strstr(text, "Linux") == NULL)
        return 4;

    if (strchr(text, 'L') == NULL)
        return 5;

    memmove(overlap + 1, overlap, 5);

    if (memcmp(overlap, "aabcde", 6) != 0)
        return 6;

    memset(text, 'x', 3);
    if (memcmp(text, "xxxinux", 7) != 0)
        return 7;

    return 0;
}
