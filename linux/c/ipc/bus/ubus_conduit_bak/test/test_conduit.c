#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include "conduit_client.h"
#include "conduit_server.h"

#include "cmockery.h"

#ifdef DEBUG
#define LOGD printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__)
#else
#define LOGD
#endif

#define ARRAY_SIZE(arg) (sizeof(arg)/sizeof(arg[0]))

static int
process_func_1(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX])
{
    assert_string_equal(req, "test_client_1");
    memmove(res, "test_server_1", strlen("test_server_1")+1);
    return 0;
}

static int
process_func_2(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX])
{
    assert_string_equal(req, "test_client_2");
    memmove(res, "test_server_2", strlen("test_server_2")+1);
    return 0;
}


static void
_request_callback(void *data, int rc, const char *content)

//typedef void (*event_callback)(const char *type, const char *str);

static module_method_t methods[] = {
    {.method_name = "m1", .fun = process_func_1},
    {.method_name = "m2", .fun = process_func_2},
};

static request_param_t request;

static void
test_server_start(void **state)
{
   // assert_int_equal(cdt_srv_start(), 0);
    int rval = cdt_srv_start();
    //assert_int_equal(rval, 0);
    *state = NULL;
    return ;
}

static void
test_server_add_module(void **state)
{
   // assert_int_equal(cdt_srv_start(), 0);
    int rval = cdt_srv_add_module("module1", methods, ARRAY_SIZE(methods));
    assert_int_equal(rval, 0);

    rval = cdt_srv_add_module("module2", methods, ARRAY_SIZE(methods));
    assert_int_equal(rval, 0);

    *state = NULL;
    return ;
}

static void
test_client_start(void **state)
{
    cdt_cli_start();
    *state = NULL;
    return ;
}

static void
test_client_stop(void **state)
{
    cdt_cli_stop();
    *state = NULL;
    return ;
}

static void
test_client_call(void **state)
{
    
    *state = NULL;
    return ;
}


static void
test_server_stop(void **state)
{
    //assert_int_equal(cdt_srv_stop(), 0);
    int rval = cdt_srv_stop();
    //assert_int_equal(rval, 0);
    *state = NULL;
    return ;
}

int main(int argc, char *argv[])
{
#if 1
    UnitTest tests[] = {
        unit_test(test_server_start),
        unit_test(test_server_add_module),
        unit_test(test_client_start),
        //call

        //event

        unit_test(test_client_stop),
        unit_test(test_server_stop),
    };
    run_tests(tests);
#else
    cdt_srv_start();
    cdt_srv_stop();
#endif
    return 0;
}
