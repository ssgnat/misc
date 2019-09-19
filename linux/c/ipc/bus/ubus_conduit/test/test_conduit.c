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

void
test_server_start(void **state)
{
    assert_int_equal(cdt_srv_start(), 0);
}

void
test_server_stop(void **state)
{
    assert_int_equal(cdt_srv_stop(), 0);
}

int main(int argc, char *argv[])
{
    UnitTest tests[] = {
        unit_test(test_server_start),
        unit_test(test_server_stop),
        //        unit_test_setup_teardown(test_, server_start, server_stop),
    };
    run_tests(tests);
    return 0;
}
