#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *file = fopen("/proc/self/mounts", "r");
    char line[4096];

    if (file == NULL) {
        perror("mounts: /proc/self/mounts");
        return 1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        char *newline = strchr(line, '\n');

        if (newline != NULL)
            *newline = '\0';

        puts(line);
    }

    if (ferror(file)) {
        perror("mounts: read");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}
