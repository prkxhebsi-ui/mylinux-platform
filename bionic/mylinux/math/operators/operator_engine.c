#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <errno.h>
#include <string.h>

/*
 * MyLinux Mathematical Operator Engine
 *
 * Operators:
 * +  Addition
 * _  Subtraction
 * *  Multiplication
 * ×  Multiplication
 * ÷  Division
 * ^  Exponentiation
 * %  Remainder
 * &  Bitwise AND
 * =  Equality
 * :  Ratio
 * $  Reserved extension
 * #  Reserved extension
 */

#define MYLINUX_OPERATOR_ABI 1

enum mylinux_operator_id {
    MYLINUX_OP_ADD = 1,
    MYLINUX_OP_SUBTRACT,
    MYLINUX_OP_MULTIPLY,
    MYLINUX_OP_DIVIDE,
    MYLINUX_OP_POWER,
    MYLINUX_OP_MODULO,
    MYLINUX_OP_BIT_AND,
    MYLINUX_OP_EQUAL,
    MYLINUX_OP_RATIO,
    MYLINUX_OP_DOLLAR,
    MYLINUX_OP_HASH
};

enum mylinux_operator_type {
    MYLINUX_TYPE_FLOAT = 1,
    MYLINUX_TYPE_INTEGER,
    MYLINUX_TYPE_BOOLEAN,
    MYLINUX_TYPE_RATIO
};

enum mylinux_operator_flags {
    MYLINUX_FLAG_BASIC = 1,
    MYLINUX_FLAG_ADVANCED = 2,
    MYLINUX_FLAG_INTEGER_ONLY = 4,
    MYLINUX_FLAG_RESERVED = 8
};

struct mylinux_operator_metadata {
    const char *symbol;
    uint32_t id;
    uint32_t precedence;
    uint32_t flags;
};

struct mylinux_number {
    double value;
    int64_t integer;
    uint32_t type;
};

struct mylinux_result {
    struct mylinux_number number;
    int error;
};

/* Read-only operator metadata. */

static const struct mylinux_operator_metadata operators[]
__attribute__((used, section(".rodata.mylinux.math.operators"))) = {
    { "+", MYLINUX_OP_ADD,      2, MYLINUX_FLAG_BASIC },
    { "_", MYLINUX_OP_SUBTRACT, 2, MYLINUX_FLAG_BASIC },
    { "*", MYLINUX_OP_MULTIPLY, 3, MYLINUX_FLAG_BASIC },
    { "×", MYLINUX_OP_MULTIPLY, 3, MYLINUX_FLAG_BASIC },
    { "÷", MYLINUX_OP_DIVIDE,   3, MYLINUX_FLAG_BASIC },
    { "^", MYLINUX_OP_POWER,    4, MYLINUX_FLAG_ADVANCED },
    { "%", MYLINUX_OP_MODULO,   3, MYLINUX_FLAG_INTEGER_ONLY },
    { "&", MYLINUX_OP_BIT_AND,  1, MYLINUX_FLAG_INTEGER_ONLY },
    { "=", MYLINUX_OP_EQUAL,    0, MYLINUX_FLAG_BASIC },
    { ":", MYLINUX_OP_RATIO,    3, MYLINUX_FLAG_ADVANCED },
    { "$", MYLINUX_OP_DOLLAR,   0, MYLINUX_FLAG_RESERVED },
    { "#", MYLINUX_OP_HASH,     0, MYLINUX_FLAG_RESERVED }
};

#define MYLINUX_OPERATOR_COUNT \
    (sizeof(operators) / sizeof(operators[0]))

static struct mylinux_result
make_result(double value, uint32_t type, int error)
{
    struct mylinux_result result = {
        .number = {
            .value = value,
            .integer = (int64_t)value,
            .type = type
        },
        .error = error
    };

    return result;
}

/* Operator lookup. */

const struct mylinux_operator_metadata *
mylinux_operator_lookup(const char *symbol)
{
    if (symbol == NULL)
        return NULL;

    for (size_t i = 0; i < MYLINUX_OPERATOR_COUNT; ++i) {
        if (strcmp(operators[i].symbol, symbol) == 0)
            return &operators[i];
    }

    return NULL;
}

/* Arithmetic operations. */

struct mylinux_result
mylinux_operator_evaluate(
    uint32_t operation,
    struct mylinux_number a,
    struct mylinux_number b)
{
    switch (operation) {
    case MYLINUX_OP_ADD:
        return make_result(
            a.value + b.value,
            MYLINUX_TYPE_FLOAT, 0);

    case MYLINUX_OP_SUBTRACT:
        return make_result(
            a.value - b.value,
            MYLINUX_TYPE_FLOAT, 0);

    case MYLINUX_OP_MULTIPLY:
        return make_result(
            a.value * b.value,
            MYLINUX_TYPE_FLOAT, 0);

    case MYLINUX_OP_DIVIDE:
        if (b.value == 0.0)
            return make_result(NAN, MYLINUX_TYPE_FLOAT, EDOM);

        return make_result(
            a.value / b.value,
            MYLINUX_TYPE_FLOAT, 0);

    case MYLINUX_OP_POWER:
        return make_result(
            pow(a.value, b.value),
            MYLINUX_TYPE_FLOAT, 0);

    case MYLINUX_OP_MODULO:
        if (a.type != MYLINUX_TYPE_INTEGER ||
            b.type != MYLINUX_TYPE_INTEGER ||
            b.integer == 0)
            return make_result(NAN, MYLINUX_TYPE_INTEGER, EDOM);

        if (a.integer == INT64_MIN && b.integer == -1)
            return make_result(0, MYLINUX_TYPE_INTEGER, 0);

        return make_result(
            (double)(a.integer % b.integer),
            MYLINUX_TYPE_INTEGER, 0);

    case MYLINUX_OP_BIT_AND:
        if (a.type != MYLINUX_TYPE_INTEGER ||
            b.type != MYLINUX_TYPE_INTEGER)
            return make_result(NAN, MYLINUX_TYPE_INTEGER, EINVAL);

        return make_result(
            (double)(a.integer & b.integer),
            MYLINUX_TYPE_INTEGER, 0);

    case MYLINUX_OP_EQUAL:
        return make_result(
            a.value == b.value ? 1.0 : 0.0,
            MYLINUX_TYPE_BOOLEAN, 0);

    case MYLINUX_OP_RATIO:
        if (b.value == 0.0)
            return make_result(NAN, MYLINUX_TYPE_RATIO, EDOM);

        return make_result(
            a.value / b.value,
            MYLINUX_TYPE_RATIO, 0);

    case MYLINUX_OP_DOLLAR:
    case MYLINUX_OP_HASH:
        return make_result(NAN, MYLINUX_TYPE_FLOAT, ENOTSUP);

    default:
        return make_result(NAN, MYLINUX_TYPE_FLOAT, EINVAL);
    }
}

/* Integer and floating-point constructors. */

struct mylinux_number
mylinux_number_float(double value)
{
    return (struct mylinux_number) {
        .value = value,
        .integer = 0,
        .type = MYLINUX_TYPE_FLOAT
    };
}

struct mylinux_number
mylinux_number_integer(int64_t value)
{
    return (struct mylinux_number) {
        .value = (double)value,
        .integer = value,
        .type = MYLINUX_TYPE_INTEGER
    };
}

/* Operator metadata access. */

size_t mylinux_operator_count(void)
{
    return MYLINUX_OPERATOR_COUNT;
}

const struct mylinux_operator_metadata *
mylinux_operator_at(size_t index)
{
    if (index >= MYLINUX_OPERATOR_COUNT)
        return NULL;

    return &operators[index];
}
