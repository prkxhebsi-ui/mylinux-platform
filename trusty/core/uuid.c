#include <trusty/uuid.h>

int trusty_uuid_is_valid(const trusty_uuid_t *uuid)
{
    if (!uuid)
        return 0;

    uint8_t value = 0;

    value |= (uint8_t)uuid->time_low;
    value |= (uint8_t)uuid->time_mid;
    value |= (uint8_t)uuid->time_hi;

    for (int i = 0; i < 2; i++)
        value |= uuid->clock_seq[i];

    for (int i = 0; i < 6; i++)
        value |= uuid->node[i];

    return value != 0;
}
