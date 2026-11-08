#include "dalvik/dex_header.h"

#include <assert.h>
#include <string.h>

int main(void) {
    struct mylinux_dex_header header;

    memset(&header, 0, sizeof(header));
    assert(mylinux_dex_validate_header(&header, sizeof(header))
           == MYLINUX_DEX_BAD_MAGIC);

    assert(mylinux_dex_validate_header(NULL, 0)
           == MYLINUX_DEX_NULL_ARGUMENT);

    return 0;
}
