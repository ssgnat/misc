#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stddef.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "unixsocket.h"


#define MAX_CONNECTION_NUMBER   10
#define MAX_BUFFER_LEN          64
#define MAX_UNIX_PATH_LEN       64


#define CLI_PERM                S_IRWXU
#define SRV_PERM                S_IRWXU

#ifdef DEBUG
#define LOGD            printf("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__)
#define LOGI(fmt, ...)  printf(fmt, __VA_ARGS__)
#else
#define LOGD
#define LOGI(fmt, ...)
#endif

static int  quit_flag = 0;
pthread_t   tid = 0;

typedef struct {
    char                        unix_path[MAX_UNIX_PATH_LEN];
    unixsock_server_receiver    unix_receiver;
} unixsock_server_info_t;

typedef struct {
    int     fd;
    char    unix_path[MAX_UNIX_PATH_LEN];
} unixsock_client_address_t;

/* * Create a server endpoint of a connection. * Returns fd if all OK,
 * <0 on error. */
int
unix_socket_listen(const char *servername)
{
    int     fd, ret, len, rval, err;
    struct  sockaddr_un un;

    LOGI("%s %s %d \n", __FILE__, __FUNCTION__, __LINE__);
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return fd;
    }

    ret = 0;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(ret)) < 0) {
    }

    LOGI("%s %s %d \n", __FILE__, __FUNCTION__, __LINE__);
    len = sizeof(un);
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, servername);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(servername);

    LOGI("%s %s %d sun_path:%s\n", __FILE__, __FUNCTION__, __LINE__,
            un.sun_path);
    unlink(un.sun_path);
    LOGD;
    if ((ret = bind(fd, (struct sockaddr *)&un, len)) < 0) {
            LOGI("%s %s %d bind errno:%d\n", __FILE__, __FUNCTION__,
                    __LINE__, errno);
    } else {

    LOGD;
        if ((ret = chmod(un.sun_path, SRV_PERM)) <  0) {
            LOGI("%s %s %d chmod errno:%d\n", __FILE__, __FUNCTION__,
                    __LINE__, errno);
        } else {

            if ((ret = listen(fd, MAX_CONNECTION_NUMBER)) < 0) {
                LOGI("%s %s %d listen errno:%d\n", __FILE__, __FUNCTION__,
                        __LINE__, errno);
            } else {
                LOGI("%s %s %d \n", __FILE__, __FUNCTION__, __LINE__);
                return fd;
            }
        }
    }

    LOGI("%s %s %d \n", __FILE__, __FUNCTION__, __LINE__);
    err = errno;
    close(fd);
    errno = err;

    return ret;
}

int
unix_socket_accept(int listenfd, unixsock_server_receiver receiver)
{
    LOGD;
    int     rval, err, maxfd, i, len;
    char    fd_[MAX_BUFFER_LEN];
    char    buffer[MAX_BUFFER_LEN];
    fd_set  fdsr;

    struct sockaddr_un  un;
    struct timeval      tv;

    unixsock_client_address_t ucas[MAX_CONNECTION_NUMBER];

    memset(&ucas, 0, sizeof(unixsock_client_address_t) * MAX_CONNECTION_NUMBER);

    rval = -2;

    while (!quit_flag) {

        FD_ZERO(&fdsr);
        FD_SET(listenfd, &fdsr);
        maxfd = listenfd + 1;

        tv.tv_sec  = 0;
        tv.tv_usec = 200000;

        for (i = 0; i < MAX_CONNECTION_NUMBER; i++) {
            if (ucas[i].fd != 0) {
                FD_SET(ucas[i].fd, &fdsr);
                if (ucas[i].fd >= maxfd) {
                    LOGD;
                    maxfd = ucas[i].fd + 1;
                }
            }
        }

        rval = select(maxfd, &fdsr, NULL, NULL, &tv);

        if (rval < 0) {
            //LOGI("%s %s %d maxfd:%d errno:%d select return:%d\n", __FILE__,
            //        __FUNCTION__, __LINE__,maxfd, errno, rval);
            continue;
        } else if (rval == 0) {
            //LOGI("%s %s %d select timeout \n", __FILE__, __FUNCTION__,
            //        __LINE__);
            continue;
        } else {

           //LOGI("maxfd:%d\n", maxfd);

        }

        for (i = 0; i < MAX_CONNECTION_NUMBER; i++) {
            if (FD_ISSET(ucas[i].fd, &fdsr)) {
                memset(buffer, 0, sizeof(buffer));
                rval = recv(ucas[i].fd, buffer, sizeof(buffer), 0);
                if (rval <= 0) {
                    close(ucas[i].fd);
                    FD_CLR(ucas[i].fd, &fdsr);
                    LOGI("%s %s %d close client:%d\n", __FILE__, __FUNCTION__,
                            __LINE__, ucas[i].fd);
                    ucas[i].fd = 0;
                    memset(&ucas[i], 0, sizeof(ucas[i]));
                } else {
                    LOGI("%s %s %d content %s from fd:%d fun:%p\n", __FILE__,
                            __FUNCTION__, __LINE__, buffer, ucas[i].fd,
                            receiver);
                    rval = receiver(ucas[i].fd, ucas[i].unix_path, buffer,
                           &rval);
                }
            }
        }

        if (FD_ISSET(listenfd, &fdsr)) {
            len = sizeof(un);
            rval = accept(listenfd, (struct sockaddr*) &un, &len);

            if (rval == -1) {
                LOGI("%s %s %d addr:%s rval:%d\n", __FILE__, __FUNCTION__,
                    __LINE__, un.sun_path, rval);
                continue;
            }

            LOGI("%s %s %d addr:%s rval:%d\n", __FILE__, __FUNCTION__,
                    __LINE__, un.sun_path, rval);

            for (i = 0; i < MAX_CONNECTION_NUMBER; i++) {
                if (ucas[i].fd == 0) {

                    ucas[i].fd = rval;
                    memmove(ucas[i].unix_path, un.sun_path,
                            sizeof(ucas[i].unix_path));

                    if (rval >= maxfd) {
                        maxfd = rval + 1;
                    }
                    break;
                }
            }


LOGD;
           if (i >= MAX_CONNECTION_NUMBER) {
               send(rval,"bye",4,0);
               close(rval);
           }
LOGD;
        }
    }

    for(i = 0; i < MAX_CONNECTION_NUMBER; i++) {
            if (ucas[i].fd != 0) {
                close(ucas[i].fd);
                ucas[i].fd = 0;
                memset(&ucas[i], 0, sizeof(ucas[i]));
            }
    }

    err = errno;
    close(listenfd);
    errno = err;

    return rval;
}


void *
unixsocket_server_func(void *argv)
{
    int ret = 0;

    unixsock_server_info_t    p;
    unixsock_server_info_t   *pval = (unixsock_server_info_t *) argv;

    strcpy(p.unix_path, pval->unix_path);
    p.unix_receiver = pval->unix_receiver;

    ret = unix_socket_listen(p.unix_path);

    if (ret <= 0) {
        LOGI("%s %s %d error:%d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        //init_status = 1;
        pthread_exit((void *) argv);

        return NULL;
    }

    LOGD;
    ret = unix_socket_accept(ret, p.unix_receiver);
    LOGD;

    pthread_exit((void *) argv);

    return NULL;
}

/*
 *@brief: start a unixsocket listening loop, call receiver when receive the
 *       request.
 *@param:
 *   unix_path: unix server path
 *   receiver:  call back function
 *@return: zero on successed, else failed
 */
int
unixsocket_server_start(const char *unix_path,
        unixsock_server_receiver receiver)
{
    int rval = 0;

    unixsock_server_info_t *t = NULL;

    t = (unixsock_server_info_t *)malloc(sizeof(unixsock_server_info_t));
    strcpy(t->unix_path, unix_path);
    t->unix_receiver = receiver;

    quit_flag = 0;
    rval = pthread_create(&tid, NULL, unixsocket_server_func, t);

    return rval;
}



 /*
  * @brief: stop unix socket listening loop, and quit.
  * @return: zero on successed, else failed
  */
int
unixsocket_server_stop(void)
{
    int   rval = 0;
    void *ret = 0;

    if (tid < 0) {

    }

    quit_flag = 1;
    rval = pthread_join(tid, &ret);
    if (rval != 0) {
       LOGI("%s %s %d pthread_join return:%d\n", __FILE__, __FUNCTION__,
               __LINE__, rval);
    } else {
       LOGI("%s %s %d pthread_join out:%d\n", __FILE__, __FUNCTION__,
               __LINE__, ret);
       free(ret);
    }

    return rval;
}


/*
 *@ brief: connect unix socket server
 *@ param:
        unix_path: less than 32 bytes
        clientid: less than 32 bytes too
 *@ return:>=0 file descriptor connected to server on successed.
            failed, error code.
 *@ author:tangss
 *@ date:  22/09/2019
 */
int
unixsocket_client_connect(const char *unix_path, const char *clientid)
{
    int fd, len, err, rval, ret;

    struct sockaddr_un un;

    len = 0;
    err = 0;
    ret = 0;

    fd = -1;
    rval = 0;

    LOGI("%s %s %d unix_path:%s clientid:%s\n", __FILE__, __FUNCTION__,
            __LINE__, unix_path, clientid);
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        LOGI("%s %s %d socket return:%d\n", __FILE__, __FUNCTION__, __LINE__,
                fd);
        return -1;
    }

    ret = 0;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &ret, sizeof(ret)) < 0) {
    }

    LOGI("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%s", unix_path, clientid);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    LOGI("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
    unlink(un.sun_path);
    ret = bind(fd, (struct sockaddr *)&un, len);
    if (ret) {
        LOGI("%s %s %d bind %s error,errno:%d\n", __FILE__, __FUNCTION__,
               __LINE__, un.sun_path, errno);
        goto failed;
    }
    LOGI("%s %s %d path:%s\n", __FILE__, __FUNCTION__, __LINE__, un.sun_path);

    if ((ret = chmod(un.sun_path, CLI_PERM)) <  0) {
        LOGI("%s %s %d chmod error errno:%d\n", __FILE__, __FUNCTION__,
                __LINE__, errno);
        goto failed;
    }

    strcpy(un.sun_path, unix_path);
    LOGI("%s %s %d %s\n", __FILE__, __FUNCTION__, __LINE__, un.sun_path);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
    ret = connect(fd, (struct sockaddr *) &un, len);
    if (ret) {
        LOGI("%s %s %d connect  errno:%d\n", __FILE__, __FUNCTION__,
                __LINE__, errno);
        goto failed;
    }

    LOGI("%s %s %d\n", __FILE__, __FUNCTION__, __LINE__);

done:
    return fd;

failed:
    close(fd);
    return -1;
}

/*
 * @brief: send buffer to sockfd
 * @return: more than 0 on successed, indicate length sent buffer
 */
int
unixsocket_client_send(int sockfd, const char *to_send_buffer,
        int to_send_buffer_len)
{

    ssize_t len = 0;

    len = send(sockfd, to_send_buffer, to_send_buffer_len, 0);
    if (len == -1) {
        LOGI("send error, errno:%d\n", errno);
    } else {
       LOGI("send successfully len:%d\n", (int)len);
    }
    return len;
}

/*
 * @brief: recive buffer from sockfd
 * @return: more than 0 on successed, indicate length received buffer
 */
int
unixsocket_client_recv(int sockfd, char *recv_buffer,
        int recv_buffer_len)
{
    ssize_t len = 0;

    //len = recv(sockfd, recv_buffer, *recv_buffer_len, 0);
    len = recv(sockfd, recv_buffer, recv_buffer_len, 0);
    LOGD;
    if (len == -1) {
        LOGI("recv error, errno:%d\n", errno);
    } else {
       LOGI("recv successfully len:%d\n", (int)len);
    }

    return len;
}

/*
 * @brief: disconnect sockfd
 * @return: more than 0 on successed, else failed
 */
int
unixsocket_client_disconnect(int sockfd)
{
    int ret = 0;

    if (sockfd > 0) {
        close(sockfd);
    }

    return ret;
}

