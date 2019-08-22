#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include "cmockery.h"
#include <stdio.h>


#define UNIXPATH    "/tmp/TESTUNIXS"
#define CLIENTID    "IAMTESTID"
#define TESTBUFFER  "0xDEADBEEF"

#define DLOG printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

int
receive(int client_fd, const char *request_buffer, int *request_buffer_len)
{
    printf("xxxxxxxx\n");
    DLOG;
    assert_true(client_fd > 0);
    DLOG;
    assert_int_equal(*request_buffer_len, sizeof(TESTBUFFER));
    DLOG;
    assert_memory_equal(request_buffer, TESTBUFFER, *request_buffer_len);

    DLOG;
    assert_int_equal(send(client_fd, request_buffer, *request_buffer_len),
            *request_buffer_len);

    DLOG;
    return 0;
}

void
test_server_start(void **state)
{
    int sockfd = 0;
    int len = 0;

    char buffer[32] = {0};

    printf("receiver func:%p\n", receive);
    int ret = unixsocket_server_start(UNIXPATH, receive);
    assert_true(ret == 0);
    *state = ret;

    usleep(1000000);
    //client send
    sockfd = unixsocket_client_connect(UNIXPATH, CLIENTID);
    assert_true(sockfd > 0);

    printf("test sockfd :%d\n", sockfd);
    len = unixsocket_client_send(sockfd, TESTBUFFER, sizeof(TESTBUFFER));
    assert_int_equal(len, sizeof(TESTBUFFER));

    len = unixsocket_client_recv(sockfd, buffer, 32);
    assert_int_equal(len, strlen(TESTBUFFER)+1);

}

void
test_server_stop(void **state)
{
    int fd = *state;

    int ret = unixsocket_server_stop();

    assert_true(ret != -1);
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
