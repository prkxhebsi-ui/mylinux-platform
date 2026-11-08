#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/params.h>
#include <openssl/param_build.h>

int main(void)
{
    int input = 42;
    int output = 0;
    OSSL_PARAM p = OSSL_PARAM_construct_int("answer", &input);

    assert(OSSL_PARAM_get_int(&p, &output));
    assert(output == 42);

    {
        OSSL_PARAM_BLD *b = OSSL_PARAM_BLD_new();
        OSSL_PARAM *params;
        const OSSL_PARAM *found;

        assert(b != NULL);
        assert(OSSL_PARAM_BLD_push_int(b, "answer", 42));
        assert(OSSL_PARAM_BLD_push_utf8_string(
            b, "name", "MyLinux", 0));

        params = OSSL_PARAM_BLD_to_param(b);
        assert(params != NULL);

        found = OSSL_PARAM_locate_const(params, "answer");
        assert(found != NULL);
        assert(OSSL_PARAM_get_int(found, &output));
        assert(output == 42);

        for (size_t i = 0; params[i].key != NULL; ++i) {
            free((void *)params[i].key);
            free(params[i].data);
        }
        free(params);
        OSSL_PARAM_BLD_free(b);
    }

    return 0;
}
