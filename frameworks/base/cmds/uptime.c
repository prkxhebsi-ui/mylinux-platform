#include <stdio.h>

int main(void)
{
    FILE *file = fopen("/proc/uptime", "r");
    double uptime = 0.0;
    double idle = 0.0;

    if (file == NULL) {
        perror("uptime: /proc/uptime");
        return 1;
    }

    if (fscanf(file, "%lf %lf", &uptime, &idle) != 2) {
        fprintf(stderr, "uptime: unable to read uptime data\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    unsigned long seconds = (unsigned long)uptime;
    unsigned long days = seconds / 86400;
    unsigned long hours = (seconds % 86400) / 3600;
    unsigned long minutes = (seconds % 3600) / 60;

    printf("up ");

    if (days > 0)
        printf("%lu days, ", days);

    printf("%lu:%02lu, idle %.2f seconds\n",
           hours, minutes, idle);

    return 0;
}
