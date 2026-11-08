#include "api_signature.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static char *copy_range(const char *begin, const char *end)
{
    if (end < begin)
        return NULL;

    size_t length = (size_t)(end - begin);
    char *copy = malloc(length + 1);

    if (!copy)
        return NULL;

    memcpy(copy, begin, length);
    copy[length] = '\0';
    return copy;
}

void sdk_free_api_signature(struct sdk_api_signature *signature)
{
    if (!signature)
        return;

    free(signature->class_name);
    free(signature->member_name);
    free(signature->return_type);

    signature->class_name = NULL;
    signature->member_name = NULL;
    signature->return_type = NULL;
}

int sdk_parse_api_signature(const char *line,
                            struct sdk_api_signature *result)
{
    if (!line || !result)
        return -1;

    result->class_name = NULL;
    result->member_name = NULL;
    result->return_type = NULL;

    while (isspace((unsigned char)*line))
        ++line;

    if (*line == '\0' || *line == '#')
        return 1;

    const char *first = strchr(line, ' ');
    if (!first)
        return -1;

    while (*first == ' ')
        ++first;

    const char *second = strchr(first, ' ');
    if (!second)
        return -1;

    const char *end = line + strlen(line);
    while (end > second && isspace((unsigned char)end[-1]))
        --end;

    result->class_name = copy_range(line, strchr(line, ' '));
    result->member_name = copy_range(first, second);

    while (*second == ' ')
        ++second;

    result->return_type = copy_range(second, end);

    if (!result->class_name || !result->member_name ||
        !result->return_type) {
        sdk_free_api_signature(result);
        return -1;
    }

    return 0;
}
