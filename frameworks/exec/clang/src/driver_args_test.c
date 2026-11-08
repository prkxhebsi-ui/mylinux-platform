#include "driver_args.h"

#include <stdio.h>
#include <string.h>

static int check(int condition, const char *message)
{
    if (!condition) {
        fprintf(stderr, "FAIL: %s\n", message);
        return 1;
    }

    printf("PASS: %s\n", message);
    return 0;
}

int main(void)
{
    struct mylinux_driver_args args;
    char error[256];
    int failures = 0;

    char *valid[] = {
        "myclang",
        "--android30-elf=yes",
        "--Werror",
        "--Wstring",
        "-c",
        "-o", "module.o",
        "--disable-runpath=yes",
        "--add-needed-libs=libc.so,libm.so",
        "--add-FUNC=entry_point,helper"
    };

    failures += check(
        mylinux_driver_parse(
            (int)(sizeof(valid) / sizeof(valid[0])),
            valid, &args, error, sizeof(error)) == 0,
        "valid custom options parse");

    failures += check(args.target == MYLINUX_ELF_ANDROID30,
                      "Android API 30 target selected");
    failures += check(args.warnings_as_errors && args.string_warnings,
                      "warning flags enabled");
    failures += check(args.compile_only && strcmp(args.output, "module.o") == 0,
                      "compile-only output parsed");
    failures += check(args.disable_runpath,
                      "RUNPATH disabled");
    failures += check(args.needed_count == 2,
                      "shared-library list parsed");
    failures += check(args.function_count == 2,
                      "function list parsed");

    {
        char *bad[] = {
            "myclang",
            "--linux-elf=yes",
            "--android30-elf=yes"
        };

        failures += check(
            mylinux_driver_parse(3, bad, &args, error, sizeof(error)) != 0,
            "conflicting ELF targets rejected");
    }

    {
        char *bad[] = {"myclang", "--Wmystery"};

        failures += check(
            mylinux_driver_parse(2, bad, &args, error, sizeof(error)) != 0,
            "unknown options rejected");
    }

    if (failures != 0) {
        fprintf(stderr, "%d test(s) failed\n", failures);
        return 1;
    }

    puts("All driver argument tests passed.");
    return 0;
}
