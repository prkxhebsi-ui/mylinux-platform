#include "systemd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

static char *trim(char *s)
{
    char *end;

    while (isspace((unsigned char)*s))
        s++;

    end = s + strlen(s);

    while (end > s && isspace((unsigned char)end[-1]))
        *--end = '\0';

    return s;
}

static int copy_value(char *dst, size_t size, const char *src)
{
    if (strlen(src) >= size)
        return -1;

    snprintf(dst, size, "%s", src);
    return 0;
}

static int parse_unit(const char *path, SDUnit *unit)
{
    FILE *fp = fopen(path, "r");
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    int section = 0;
    int have_exec = 0;

    if (!fp)
        return -1;

    while ((length = getline(&line, &capacity, fp)) >= 0) {
        char *p = trim(line);
        char *equal;

        (void)length;

        if (!*p || *p == '#' || *p == ';')
            continue;

        if (*p == '[') {
            if (strcmp(p, "[Unit]") == 0)
                section = 1;
            else if (strcmp(p, "[Service]") == 0)
                section = 2;
            else
                section = 0;

            continue;
        }

        equal = strchr(p, '=');
        if (!equal)
            continue;

        *equal++ = '\0';

        char *key = trim(p);
        char *value = trim(equal);

        if (section == 1 && strcmp(key, "Description") == 0) {
            if (copy_value(unit->description,
                           sizeof(unit->description), value) < 0)
                goto invalid;
        }

        if (section == 2 && strcmp(key, "ExecStart") == 0) {
            if (copy_value(unit->exec_start,
                           sizeof(unit->exec_start), value) < 0)
                goto invalid;
            have_exec = 1;
        }

        if (section == 2 && strcmp(key, "Restart") == 0) {
            if (copy_value(unit->restart,
                           sizeof(unit->restart), value) < 0)
                goto invalid;
        }

        if (section == 2 && strcmp(key, "Type") == 0 &&
            strcmp(value, "simple") != 0) {
            fprintf(stderr, "systemd: unsupported service Type=%s in %s\n",
                    value, path);
            goto invalid;
        }
    }

    free(line);
    fclose(fp);

    if (!have_exec) {
        fprintf(stderr, "systemd: missing ExecStart in %s\n", path);
        return -1;
    }

    return 0;

invalid:
    free(line);
    fclose(fp);
    return -1;
}

static void insert_sorted(SDUnit **head, SDUnit *unit)
{
    SDUnit **position = head;

    while (*position &&
           strcmp((*position)->name, unit->name) < 0)
        position = &(*position)->next;

    unit->next = *position;
    *position = unit;
}

SDUnit *sd_load_units(const char *directory)
{
    DIR *dir = opendir(directory);
    struct dirent *entry;
    SDUnit *head = NULL;

    if (!dir) {
        perror("systemd: opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        size_t length = strlen(entry->d_name);

        if (length < 9 ||
            strcmp(entry->d_name + length - 8, ".service") != 0)
            continue;

        SDUnit *unit = calloc(1, sizeof(*unit));
        if (!unit)
            break;

        if (copy_value(unit->name, sizeof(unit->name),
                       entry->d_name) < 0) {
            free(unit);
            continue;
        }

        strcpy(unit->restart, "no");

        char path[1024];
        if (snprintf(path, sizeof(path), "%s/%s",
                     directory, entry->d_name) >= (int)sizeof(path)) {
            free(unit);
            continue;
        }

        if (parse_unit(path, unit) < 0) {
            free(unit);
            continue;
        }

        insert_sorted(&head, unit);
    }

    closedir(dir);
    return head;
}

void sd_free_units(SDUnit *units)
{
    while (units) {
        SDUnit *next = units->next;
        free(units);
        units = next;
    }
}

int sd_check_units(SDUnit *units)
{
    int count = 0;

    for (SDUnit *u = units; u; u = u->next) {
        printf("UNIT:        %s\n", u->name);
        printf("DESCRIPTION: %s\n",
               u->description[0] ? u->description : "(none)");
        printf("EXECSTART:   %s\n", u->exec_start);
        printf("RESTART:     %s\n\n", u->restart);
        count++;
    }

    printf("Loaded service units: %d\n", count);
    return count ? 0 : -1;
}
