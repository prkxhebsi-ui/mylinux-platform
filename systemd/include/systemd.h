#ifndef MYLINUX_SYSTEMD_H
#define MYLINUX_SYSTEMD_H

#include <sys/types.h>

#define SD_NAME_MAX 128
#define SD_DESC_MAX 256
#define SD_EXEC_MAX 512
#define SD_RESTART_MAX 32

typedef struct SDUnit {
    char name[SD_NAME_MAX];
    char description[SD_DESC_MAX];
    char exec_start[SD_EXEC_MAX];
    char restart[SD_RESTART_MAX];
    pid_t pid;
    int active;
    struct SDUnit *next;
} SDUnit;

SDUnit *sd_load_units(const char *directory);
void sd_free_units(SDUnit *units);
int sd_check_units(SDUnit *units);
int sd_manager_run(SDUnit *units);
int sd_android_check(void);

#endif
