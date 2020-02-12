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


static volatile int c_cnt = 0;
static volatile int s_cnt = 0;

static int process_func_1(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX]);
static int process_func_2(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX]);
static void
_response_callback_1(void *auxiliary, int resp_code, const char *resp_content);
static void
_response_callback_2(void *auxiliary, int resp_code, const char *resp_content);

static char srvevents[][MAX_EVENT_LEN] = {
    "srvevent1",
    "srvevent2",
};

static char srveventcontents[][MAX_EVENT_LEN] = {
    "srveventcontent1",
    "srveventcontent2",
};

static char clievents[][MAX_EVENT_LEN] = {
    "clievent1",
    "clievent2",
};

static char clieventcontents[][MAX_EVENT_LEN] = {
    "clieventcontent1",
    "clieventcontent2",
};


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

static int
process_func_1(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX])
{
    //assert_string_equal(req, "test_client_1");
    memmove(res, "test_server_1", strlen("test_server_1")+1);

    return 0;
}

static int
process_func_2(const char *req, char res[CUSTOM_OBJECT_NAME_LEN_MAX])
{
    //assert_string_equal(req, "test_client_2");
    memmove(res, "test_server_2", strlen("test_server_2")+1);
    return 0;
}

static void
_response_callback_1(void *auxiliary, int resp_code, const char *resp_content)
{
    //assert_string_equal(auxiliary, "auxiliary_1");
    //assert_string_equal(resp_content, "test_server_1");
    //assert_int_equal(resp_code, 0);

    //printf("1 auxiliary:%s\n", (char *)auxiliary);
    //printf("1 rc:%d\n",  resp_code);
    //printf("1 content:%s\n",  resp_content);
    printf("cr - time:%d\n", s_cnt++);

    return ;
}
static void
_response_callback_2(void *auxiliary, int resp_code, const char *resp_content)
{
    //assert_string_equal(auxiliary, "auxiliary_2");
    //assert_string_equal(resp_content, "test_server_2");
   // assert_int_equal(resp_code, 0);

    //printf("2 auxiliary:%s\n", (char *)auxiliary);
    //printf("2 rc:%d\n",  resp_code);
    //printf("2 content:%s\n",  resp_content);
    printf("cr - time:%d\n", s_cnt++);
    return ;
}

static void
srv_event_callback(const char *type, const char *str)
{
    int i = -1;
    int j = -1;

    printf("er-srv-time:%d\n", s_cnt++);
//    printf("event_callback type:%s content:%s\n", type, str);

    return;

    for (i = 0; i < ARRAY_SIZE(srvevents); i++) {
        if (j) {
            j = strcmp(type, srvevents[i]);
        }
    }
    //assert_true(j == 0);

    j = -1;
    for (i = 0; i < ARRAY_SIZE(srveventcontents); i++) {
        if (j < 0) {
            j = strstr(srveventcontents[i], str);
        }
    }
    //assert_true(j >= 0);

    return ;
}

static void
test_server_send_event(void **state)
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE(clievents); i++) {
        printf("es-srv-time:%d events:%s\n", c_cnt++, clievents[i]);
        cdt_srv_send_event(clievents[i], clieventcontents[i]);
    }

    return ;
}

static void
cli_event_callback(const char *type, const char *str)
{
    int i = -1;
    int j = -1;


    printf("er-cli-time:%d\n", s_cnt++);
    printf("event_callback type:%s content:%s\n", type, str);

    return ;
    for (i = 0; i < ARRAY_SIZE(clievents); i++) {
        if (j) {
            j = strcmp(type, clievents[i]);
        }
    }
   // assert_true(j == 0);

    j = -1;
    for (i = 0; i < ARRAY_SIZE(clieventcontents); i++) {
        if (j < 0) {
            j = strstr(clieventcontents[i], str);
        }
    }
    //assert_true(j >= 0);

    return ;
}

static void
test_server_start(void **state)
{
   // assert_int_equal(cdt_srv_start(), 0);
    int rval = cdt_srv_start();
//    assert_int_equal(rval, 0);
    return ;
}

static void
test_server_run(void **state)
{
    cdt_srv_run();
    return ;
}
static void
test_server_add_module(void **state)
{
   // assert_int_equal(cdt_srv_start(), 0);

    printf("add_module b\n");
    int rval = cdt_srv_add_module("module2", methods, ARRAY_SIZE(methods));
//    assert_int_equal(rval, 0);

    rval = cdt_srv_add_module("module1", methods, ARRAY_SIZE(methods));
 //   assert_int_equal(rval, 0);
    printf("add_module e\n");

    return ;
}

static void
test_client_start(void **state)
{
    cdt_cli_start();
    return ;
}

static void
test_client_stop(void **state)
{
    //cdt_cli_stop();
    return ;
}

static void
test_client_call(void **state)
{
    printf("cs - time:%d\n", c_cnt++);
    cdt_cli_request(request1, "module1", "m1", "test_client_1");
    printf("cs - time:%d\n", c_cnt++);
    cdt_cli_request(request2, "module2", "m2", "test_client_2");

    return ;
}


static void
test_client_send_event(void **state)
{
    int i = 0;

    for (i = 0; i < ARRAY_SIZE(srvevents); i++) {
        printf("es-cli-time:%d\n", c_cnt++);
        //usleep(10000);
        cdt_cli_send_event(srvevents[i], srveventcontents[i]);
    }

    return ;
}

static void
test_client_register_event(void **state)
{

    cdt_cli_register_events(clievents, ARRAY_SIZE(clievents), cli_event_callback);

    return ;
}

static void
test_server_register_event(void **state)
{

    cdt_srv_register_events(srvevents, ARRAY_SIZE(srvevents), srv_event_callback);

    return ;
}

static void
test_server_stop(void **state)
{
    sleep(10);
    //assert_int_equal(cdt_srv_stop(), 0);
 //   int rval = cdt_srv_stop();
    //assert_int_equal(rval, 0);
    return ;
}

int main(int argc, char *argv[])
{
#ifdef TEST_CALL
#ifdef CLIENT
    printf("=============================================\n");
    printf("=================TEST_CALL CLIENT============\n");
    printf("=============================================\n");

    sleep(5);
    test_client_start(NULL);
    while (c_cnt < 5000) {
        test_client_call(NULL);
        //printf("TIME:%d\n", c_cnt++);
    }
    test_client_stop(NULL);
    return 0;
#else
    printf("=============================================\n");
    printf("=================TEST_CALL SERVER============\n");
    printf("=============================================\n");
    test_server_start(NULL);
    test_server_add_module(NULL);
    test_server_run(NULL);
    test_server_stop(NULL);
    return 0;
#endif
#endif

#ifdef TEST_SRV_EVENTS
#ifdef CLIENT
    printf("=============================================\n");
    printf("===========TEST_SRV_EVENTS CLIENT============\n");
    printf("=============================================\n");

    sleep(5);
    test_client_start(NULL);
    while (c_cnt < 5000) {
        test_client_send_event(NULL);
        //usleep(10000);
        //printf("TIME:%d\n", c_cnt++);
    }
    test_client_stop(NULL);
    sleep(5);
    return 0;
#else
    printf("=============================================\n");
    printf("===========TEST_SRV_EVENTS SERVER============\n");
    printf("=============================================\n");
    test_server_start(NULL);
    test_server_register_event(NULL);
    test_server_run(NULL);
    test_server_stop(NULL);
    return 0;
#endif
#endif


#ifdef TEST_CLI_EVENTS
#ifdef CLIENT
    printf("=============================================\n");
    printf("===========TEST_CLI_EVENTS CLIENT============\n");
    printf("=============================================\n");

    test_client_start(NULL);
    test_client_register_event(NULL);
    test_client_stop(NULL);
    sleep(5);
    return 0;
#else
    printf("=============================================\n");
    printf("===========TEST_CLI_EVENTS SERVER============\n");
    printf("=============================================\n");
    test_server_start(NULL);
    while (c_cnt < 5000) {
        test_server_send_event(NULL);
        usleep(10000);
    }
    test_server_stop(NULL);
    return 0;
#endif
#endif

    return 0;
}
