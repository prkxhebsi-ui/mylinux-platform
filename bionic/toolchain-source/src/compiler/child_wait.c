#include "child_wait.h"

#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int compiler_wait_child(int pid, int *exit_code)
{
    int status;
    pid_t result;

    if (pid <= 0) {
        errno = EINVAL;
        return -1;
    }

    do {
        result = waitpid((pid_t)pid, &status, 0);
    } while (result < 0 && errno == EINTR);

    if (result < 0) {
        return -1;
    }

    if (exit_code != 0) {
        if (WIFEXITED(status)) {
            *exit_code = WEXITSTATUS(status);
        } else if (WIFSIGNALED(status)) {
            *exit_code = 128 + WTERMSIG(status);
        } else {
            *exit_code = -1;
        }
    }

    return 0;
}
