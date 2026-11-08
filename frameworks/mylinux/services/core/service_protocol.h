#ifndef MYLINUX_SERVICE_PROTOCOL_H
#define MYLINUX_SERVICE_PROTOCOL_H

#define ML_SERVICE_ACTIVITY "activity"
#define ML_SERVICE_PACKAGE  "package"
#define ML_SERVICE_WINDOW   "window"
#define ML_SERVICE_LOGIN    "login"
#define ML_SERVICE_POWER    "power"

#define ML_SERVICE_OK          0
#define ML_SERVICE_ERROR       1
#define ML_SERVICE_NOT_FOUND   2
#define ML_SERVICE_NOT_IMPL    3
#define ML_SERVICE_PERMISSION  4

struct ml_service {
    const char *name;
    const char *description;

    int (*start)(void);
    int (*stop)(void);
    int (*command)(int argc, char **argv);
};

#endif
