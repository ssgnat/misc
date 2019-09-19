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

static char events[][MAX_EVENT_LEN] = {
    "event1",
    "event2",
};
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
_response_callback_1(void *auxiliary, int resp_code, const char *resp_content)
{
    assert_string_equal(auxiliary, "auxiliary_1");
    assert_string_equal(resp_content, "test_server_1");
    assert_int_equal(resp_code, 0);

    printf("1 auxiliary:%s\n", (char *)auxiliary);
    printf("1 rc:%d\n",  resp_code);
    printf("1 content:%s\n",  resp_content);

    return ;
}
static void
_response_callback_2(void *auxiliary, int resp_code, const char *resp_content)
{
    assert_string_equal(auxiliary, "auxiliary_2");
    assert_string_equal(resp_content, "test_server_2");
    assert_int_equal(resp_code, 0); 

    printf("2 auxiliary:%s\n", (char *)auxiliary);
    printf("2 rc:%d\n",  resp_code);
    printf("2 content:%s\n",  resp_content);

    return ;
}

static void
_event_callback(const char *type, const char *str)
{
    int i = -1;
    int j = -1;

    printf("event_callback type:%s content:%s\n", type, str);

    i = strcmp(type, "event1");
    j = strcmp(type, "event2");
    //assert_true( i == 0 || j == 0);

    i = strcmp(type, "eventcontent1");
    i = strcmp(type, "eventcontent2");
    //assert_true( i == 0 || j == 0);

    return ;
}

static module_method_t methods[] = {
    {.method_name = "m1", .fun = process_func_1},
    {.method_name = "m2", .fun = process_func_2},
};

static response_handler_t request1 = {
    .callback  = _response_callback_1,
    .auxiliary = "auxiliary_1",
};

static response_handler_t request2 = {
    .callback  = _response_callback_2,
    .auxiliary = "auxiliary_2",
};

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

    cdt_cli_request(request1, "module1", "m1", "test_client_1");
    cdt_cli_request(request2, "module2", "m2", "test_client_2");

    *state = NULL;
    return ;
}


static void
test_client_send_event(void **state)
{

    cdt_cli_send_event("event1", "eventcontent1");
    cdt_cli_send_event("event2", "eventcontent2");

    sleep(2);
    *state = NULL;
    return ;
}


static void
test_server_register_event(void **state)
{

    assert_int_equal(cdt_srv_register_events(events, _event_callback), 0);

    *state = NULL;
    return ;
}
static void
test_server_stop(void **state)
{
//    sleep(50);
    //assert_int_equal(cdt_srv_stop(), 0);
 //   int rval = cdt_srv_stop();
    //assert_int_equal(rval, 0);
    *state = NULL;
    return ;
}

int main(int argc, char *argv[])
{
#if 1
    pid_t pid;
    pid = fork();
    if(pid < 0)
    {
        perror("fork failed");
        exit(1);
    }

    if(pid == 0)
    {
        printf("This is the child process. My PID is: %d. My PPID is: %d.\n",
                getpid(), getppid());
        sleep(1);
        UnitTest tests[] = {
            unit_test(test_client_start),
            //call
            unit_test(test_client_call),
            //event
            unit_test(test_client_send_event),

            unit_test(test_client_stop),
        };
        run_tests(tests);
        sleep(5);
    }
    else
    {
        printf("This is the parent process. My PID is %d.\n", getpid());
        UnitTest tests[] = {
            unit_test(test_server_start),
            unit_test(test_server_add_module),
            //event
            unit_test(test_server_register_event),
            unit_test(test_server_stop),
        };
        run_tests(tests);
        sleep(5);
    }
#else
    cdt_srv_start();
    cdt_srv_stop();
#endif
    return 0;
}
