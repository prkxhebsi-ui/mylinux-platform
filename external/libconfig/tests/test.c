#include "libconfig/config.h"
#include <stdio.h>

int main(void) {
    lc_config config = {0};

    if (lc_load(&config, "test.conf") != 0) {
        puts("Could not load configuration");
        return 1;
    }

    printf("Device: %s\n", lc_get(&config, "device"));
    printf("Architecture: %s\n", lc_get(&config, "architecture"));

    lc_free(&config);
    return 0;
}
