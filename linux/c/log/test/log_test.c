#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "log.h"
#include "cmockery.h"

void
test_log(void **state)
{
    LOGI("");
    LOGD("");
    LOGE("");

    LOGI("1");
    LOGD("2");
    LOGE("3");

    LOGI("%s","FMT ARGS");
    LOGD("%s","FMT ARGS");
    LOGE("%s","FMT ARGS");
}

int main(int argc, char *argv[])
{
    UnitTest tests[] = {
        unit_test(test_log),
    };
    run_tests(tests);
    return 0;
}
