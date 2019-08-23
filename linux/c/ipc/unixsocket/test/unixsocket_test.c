#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdio.h>
#include <errno.h>
#include <pthread.h>

#include "cmockery.h"

#define UNIXPATH    "/tmp/TESTUNIXS"
#define CLIENTID    "IAMTESTID"
#define TESTBUFFER  "0xDEADBEEF"

#ifdef DEBUG
#define LOGD printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__)
#else
#define LOGD
#endif

int
receive(int client_fd, const char *clientpath, const char *request_buffer,
        int *request_buffer_len)
{
    LOGD;
    printf("--receive client path:%s\n", clientpath);
    assert_true(client_fd > 0);
    LOGD;
    assert_int_equal(*request_buffer_len, sizeof(TESTBUFFER));
    LOGD;
    assert_memory_equal(request_buffer, TESTBUFFER, *request_buffer_len);

    LOGD;
    assert_int_equal(send(client_fd, request_buffer, *request_buffer_len),
            *request_buffer_len);

    LOGD;
    return 0;
}

#if 1 
void *
test_client_func(void *argv)
{
    int     sockfd, retries, len, id;
    char    buffer[32] = {0};
    char    clientid[32] = {0};

    sockfd = 0;
    retries = 0;

    len = 0;

    id = (int)argv;

    sprintf(clientid, "%s%d", CLIENTID, id);
    printf("clientid len:%d\n", strlen(clientid));

    //client send
    while (!sockfd && retries++ < 10) {
        usleep(100000);
        sockfd = unixsocket_client_connect(UNIXPATH, clientid);
    }

    assert_true(sockfd > 0);

    len = unixsocket_client_send(sockfd, TESTBUFFER, sizeof(TESTBUFFER));
    assert_int_equal(len, sizeof(TESTBUFFER));

    len = unixsocket_client_recv(sockfd, buffer, 32);
    assert_int_equal(len, strlen(TESTBUFFER)+1);

    pthread_exit(&id);
}
#endif

void
test_server_start(void **state)
{
    int     sockfd, times, rval;
    char    buffer[32] = {0};
    void   *r;

    pthread_t threadids[10];

    sockfd = 0;
    times = 0;

    int ret = unixsocket_server_start(UNIXPATH, receive);
    assert_true(ret == 0);
    *state = ret;

#if 1
    while (times < 10) {
      rval = pthread_create(&threadids[times], NULL, test_client_func, times);
      if (rval != 0) {
          printf("%s %s %d errno:%d pthread_create\n", __FILE__, __FUNCTION__,
                  __LINE__, errno);
      }
      printf("create times:%d\n",times);
      times++;
    }

    times = 0;
    while (times < 10) {
        pthread_join(threadids[times], &r);
        printf("exit:%d\n", (int*)r);
        times++;
    }
#else

    int retries = 0;
    int len = 0;
    while (!sockfd && retries++ < 10) {
        usleep(100000);
        sockfd = unixsocket_client_connect(UNIXPATH, "x");
    }

    assert_true(sockfd > 0);

    len = unixsocket_client_send(sockfd, TESTBUFFER, sizeof(TESTBUFFER));
    assert_int_equal(len, sizeof(TESTBUFFER));

    len = unixsocket_client_recv(sockfd, buffer, 32);
    assert_int_equal(len, strlen(TESTBUFFER)+1);

#endif

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
