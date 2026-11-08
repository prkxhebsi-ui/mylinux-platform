#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define AM_VERSION "0.1"

struct am_command {
    const char *name;
    const char *description;
};

static const struct am_command commands[] = {
    {"start", "Start an activity"},
    {"startservice", "Start a service"},
    {"start-foreground-service", "Start a foreground service"},
    {"stopservice", "Stop a service"},
    {"broadcast", "Send a broadcast intent"},
    {"instrument", "Run instrumentation"},
    {"profile", "Profile an application process"},
    {"dumpheap", "Dump an application heap"},
    {"set-debug-app", "Set an application for debugging"},
    {"clear-debug-app", "Clear the debug application"},
    {"set-watch-heap", "Monitor application heap usage"},
    {"clear-watch-heap", "Clear heap monitoring"},
    {"clear-exit-info", "Clear process exit information"},
    {"bug-report", "Request a system bug report"},
    {"force-stop", "Force-stop an application"},
    {"crash", "Crash an application process"},
    {"kill", "Kill background application processes"},
    {"kill-all", "Kill safe cached processes"},
    {"make-uid-idle", "Make an application UID idle"},
    {"monitor", "Monitor application crashes and ANRs"},
    {"watch-uids", "Monitor UID state changes"},
    {"hang", "Hang the system"},
    {"restart", "Restart user-space services"},
    {"idle-maintenance", "Run idle maintenance"},
    {"screen-compat", "Control screen compatibility"},
    {"package-importance", "Show package importance"},
    {"to-uri", "Convert an intent to a URI"},
    {"to-intent-uri", "Convert an intent to an intent URI"},
    {"to-app-uri", "Convert an intent to an android-app URI"},
    {"switch-user", "Switch the foreground user"},
    {"get-current-user", "Get the foreground user"},
    {"start-user", "Start a user"},
    {"unlock-user", "Unlock a user"},
    {"stop-user", "Stop a user"},
    {"is-user-stopped", "Check whether a user is stopped"},
    {"get-started-user-state", "Get a user's started state"},
    {"track-associations", "Enable association tracking"},
    {"untrack-associations", "Disable association tracking"},
    {"get-uid-state", "Get a UID process state"},
    {"attach-agent", "Attach an agent to a process"},
    {"get-config", "Get device configuration"},
    {"supports-multiwindow", "Check multiwindow support"},
    {"supports-split-screen-multi-window", "Check split-screen support"},
    {"suppress-resize-config-changes", "Suppress resize configuration changes"},
    {"set-inactive", "Set an application inactive state"},
    {"get-inactive", "Get an application inactive state"},
    {"set-standby-bucket", "Set an application standby bucket"},
    {"get-standby-bucket", "Get an application standby bucket"},
    {"send-trim-memory", "Send a memory trim event"},
    {"display", "Display management commands"},
    {"stack", "Activity stack management commands"},
    {"task", "Activity task management commands"},
    {"update-appinfo", "Update application information"},
    {"write", "Write pending Activity Manager state"},
    {"compat", "Application compatibility commands"}
};

static void print_usage(const char *program)
{
    printf("MyLinux Activity Manager %s\n", AM_VERSION);
    printf("Usage: %s [options] COMMAND [arguments]\n\n", program);

    printf("Options:\n");
    printf("  -h, --help       Show this help\n");
    printf("  --version        Show version\n\n");

    printf("Activity commands:\n");
    printf("  start\n");
    printf("  startservice\n");
    printf("  start-foreground-service\n");
    printf("  stopservice\n");
    printf("  broadcast\n");
    printf("  instrument\n\n");

    printf("Process and debugging commands:\n");
    printf("  profile\n");
    printf("  dumpheap\n");
    printf("  set-debug-app\n");
    printf("  clear-debug-app\n");
    printf("  set-watch-heap\n");
    printf("  clear-watch-heap\n");
    printf("  force-stop\n");
    printf("  crash\n");
    printf("  kill\n");
    printf("  kill-all\n");
    printf("  monitor\n");
    printf("  watch-uids\n\n");

    printf("User commands:\n");
    printf("  get-current-user\n");
    printf("  switch-user\n");
    printf("  start-user\n");
    printf("  unlock-user\n");
    printf("  stop-user\n");
    printf("  is-user-stopped\n");
    printf("  get-started-user-state\n\n");

    printf("Configuration and maintenance:\n");
    printf("  get-config\n");
    printf("  supports-multiwindow\n");
    printf("  supports-split-screen-multi-window\n");
    printf("  idle-maintenance\n");
    printf("  bug-report\n");
    printf("  restart\n");
    printf("  write\n\n");

    printf("Other commands:\n");
    printf("  display, stack, task, compat\n");
    printf("  package-importance, get-uid-state\n");
    printf("  set-inactive, get-inactive\n");
    printf("  set-standby-bucket, get-standby-bucket\n");
    printf("  send-trim-memory, attach-agent\n");
    printf("  to-uri, to-intent-uri, to-app-uri\n\n");

    printf("Use '%s COMMAND --help' where supported for command details.\n",
           program);
}

static const struct am_command *find_command(const char *name)
{
    size_t count = sizeof(commands) / sizeof(commands[0]);

    for (size_t i = 0; i < count; i++) {
        if (strcmp(commands[i].name, name) == 0)
            return &commands[i];
    }

    return NULL;
}

static int validate_arguments(const char *command, int argc)
{
    if (!strcmp(command, "get-current-user") ||
        !strcmp(command, "kill-all") ||
        !strcmp(command, "clear-debug-app") ||
        !strcmp(command, "clear-watch-heap") ||
        !strcmp(command, "monitor") ||
        !strcmp(command, "watch-uids") ||
        !strcmp(command, "idle-maintenance") ||
        !strcmp(command, "restart") ||
        !strcmp(command, "write") ||
        !strcmp(command, "supports-multiwindow") ||
        !strcmp(command, "supports-split-screen-multi-window") ||
        !strcmp(command, "track-associations") ||
        !strcmp(command, "untrack-associations") ||
        !strcmp(command, "bug-report")) {
        return 0;
    }

    if (!strcmp(command, "force-stop") ||
        !strcmp(command, "kill") ||
        !strcmp(command, "crash") ||
        !strcmp(command, "package-importance") ||
        !strcmp(command, "get-uid-state") ||
        !strcmp(command, "get-config") ||
        !strcmp(command, "switch-user") ||
        !strcmp(command, "start-user") ||
        !strcmp(command, "stop-user") ||
        !strcmp(command, "unlock-user") ||
        !strcmp(command, "is-user-stopped") ||
        !strcmp(command, "get-started-user-state")) {
        if (argc < 1)
            return -1;
    }

    if (!strcmp(command, "start") ||
        !strcmp(command, "startservice") ||
        !strcmp(command, "start-foreground-service") ||
        !strcmp(command, "stopservice") ||
        !strcmp(command, "broadcast") ||
        !strcmp(command, "instrument")) {
        if (argc < 1)
            return -1;
    }

    return 0;
}

static int execute_command(const char *command, int argc, char **argv)
{
    (void) argv;

    if (!strcmp(command, "help") ||
        !strcmp(command, "--help") ||
        !strcmp(command, "-h")) {
        print_usage("am");
        return 0;
    }

    if (argc > 0 && !strcmp(argv[0], "--help")) {
        printf("Usage: am %s [arguments]\n", command);
        return 0;
    }

    if (validate_arguments(command, argc) != 0) {
        fprintf(stderr, "am: missing required argument for '%s'\n",
                command);
        fprintf(stderr, "Try 'am --help'.\n");
        return 2;
    }

    /*
     * The Activity Manager backend is not connected yet.
     * Never report success for an operation that did not happen.
     */
    fprintf(stderr,
            "am: '%s': Activity Manager service is not connected "
            "(ENOSYS)\n",
            command);

    return 3;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage(argv[0]);
        return 0;
    }

    if (!strcmp(argv[1], "--version")) {
        printf("MyLinux Activity Manager %s\n", AM_VERSION);
        return 0;
    }

    if (!strcmp(argv[1], "--help") ||
        !strcmp(argv[1], "-h") ||
        !strcmp(argv[1], "help")) {
        print_usage(argv[0]);
        return 0;
    }

    const struct am_command *cmd = find_command(argv[1]);

    if (!cmd) {
        fprintf(stderr, "am: unknown command '%s'\n", argv[1]);
        fprintf(stderr, "Try 'am --help'.\n");
        return 2;
    }

    return execute_command(cmd->name, argc - 2, argv + 2);
}
