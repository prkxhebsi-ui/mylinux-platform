#include "systemd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

static volatile sig_atomic_t stopping = 0;

static void stop_handler(int signal_number)
{
    (void)signal_number;
    stopping = 1;
}

static int make_argv(const char *command, char *storage,
                     size_t storage_size, char **argv, size_t max_args)
{
    size_t i = 0;
    size_t argc = 0;
    int quoted = 0;
    char quote = 0;

    if (strlen(command) >= storage_size)
        return -1;

    strcpy(storage, command);

    while (storage[i] && argc + 1 < max_args) {
        while (storage[i] == ' ' || storage[i] == '\t')
            i++;

        if (!storage[i])
            break;

        argv[argc++] = &storage[i];

        while (storage[i]) {
            if ((storage[i] == '"' || storage[i] == '\'') &&
                (!quoted || storage[i] == quote)) {
                if (!quoted) {
                    quoted = 1;
                    quote = storage[i];
                } else {
                    quoted = 0;
                }

                memmove(&storage[i], &storage[i + 1],
                        strlen(&storage[i]));
                continue;
            }

            if (!quoted &&
                (storage[i] == ' ' || storage[i] == '\t')) {
                storage[i++] = '\0';
                break;
            }

            i++;
        }

        if (quoted)
            return -1;
    }

    argv[argc] = NULL;
    return argc ? (int)argc : -1;
}

static pid_t start_service(SDUnit *unit)
{
    char storage[SD_EXEC_MAX];
    char *argv[32];

    if (make_argv(unit->exec_start, storage,
                  sizeof(storage), argv, 32) < 0) {
        fprintf(stderr, "systemd: invalid command for %s\n", unit->name);
        return -1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("systemd: fork");
        return -1;
    }

    if (pid == 0) {
        signal(SIGTERM, SIG_DFL);
        signal(SIGINT, SIG_DFL);
        signal(SIGCHLD, SIG_DFL);

        execvp(argv[0], argv);
        perror("systemd: exec");
        _exit(127);
    }

    unit->pid = pid;
    unit->active = 1;

    printf("systemd: started %s (PID %ld)\n",
           unit->name, (long)pid);

    return pid;
}

int sd_manager_run(SDUnit *units)
{
    if (getpid() != 1) {
        fprintf(stderr,
                "systemd: refusing to run services outside PID 1\n");
        return 1;
    }

    struct sigaction action;
    memset(&action, 0, sizeof(action));
    action.sa_handler = stop_handler;
    sigemptyset(&action.sa_mask);

    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    printf("systemd: MyLinux service manager starting\n");

    for (SDUnit *u = units; u && !stopping; u = u->next)
        start_service(u);

    while (!stopping) {
        int status;
        pid_t pid = waitpid(-1, &status, 0);

        if (pid < 0) {
            if (errno == EINTR)
                continue;
            if (errno == ECHILD)
                break;
            perror("systemd: waitpid");
            break;
        }

        for (SDUnit *u = units; u; u = u->next) {
            if (u->pid != pid)
                continue;

            u->active = 0;
            u->pid = 0;

            printf("systemd: %s exited\n", u->name);

            if (strcmp(u->restart, "always") == 0 ||
                (strcmp(u->restart, "on-failure") == 0 &&
                 (!WIFEXITED(status) || WEXITSTATUS(status) != 0))) {
                if (!stopping)
                    start_service(u);
            }
            break;
        }
    }

    printf("systemd: stopping services\n");

    for (SDUnit *u = units; u; u = u->next) {
        if (u->active && u->pid > 0)
            kill(u->pid, SIGTERM);
    }

    while (waitpid(-1, NULL, 0) > 0)
        ;

    return 0;
}
