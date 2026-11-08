#ifndef MYLINUX_API_SIGNATURE_H
#define MYLINUX_API_SIGNATURE_H

#include <stddef.h>

struct sdk_api_signature {
    char *class_name;
    char *member_name;
    char *return_type;
};

int sdk_parse_api_signature(const char *line,
                            struct sdk_api_signature *result);
void sdk_free_api_signature(struct sdk_api_signature *signature);

#endif
