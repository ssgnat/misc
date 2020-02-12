




#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <libubox/ustream.h>
#include <libubox/blobmsg_json.h>
#include <pthread.h>

#include "libubus.h"
#include "conduit_common.h"
#include "conduit_client.h"

//#include "count.h"
//#include "ubus_app_error.h"
//#include "ubus_server_command.h"

#define debug 0
#define MAX_BLOB_BUF 50

#define DEFAULT_CDT_REQUEST_TIMETOUT 5000
#define MAX_RESULT_BUFFER 20480


typedef struct blob_attr blob_attr_t;

enum {
    RETURN_CODE,
    RETURN_DATA,
    RETURN_MAX,
};

static struct ubus_context *_ubus_context;
static struct ubus_event_handler _listerner;

#if 0
static struct blob_buf _blob_event;
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

static event_callback _event_callback;

static const struct blobmsg_policy _return_policy[RETURN_MAX] = {
    [RETURN_CODE] = { .name = "rc", .type = BLOBMSG_TYPE_INT32 },
    [RETURN_DATA] = { .name = "data", .type = BLOBMSG_TYPE_STRING },
};

static int
exec(const char *command, char *with_result, int *with_result_len);

static int
str_replace(char *p_result, char* p_source, char* p_seach, char *p_repstr)
{
    int c = 0;
    int repstr_leng = 0;
    int searchstr_leng = 0;
    char *p1;
    char *presult = p_result;
    char *psource = p_source;
    char *prep = p_repstr;
    char *pseach = p_seach;
    int nLen = 0;
    repstr_leng = strlen(prep);
    searchstr_leng = strlen(pseach);

    do {
        p1 = strstr(psource, p_seach);
        if (p1 == 0)
        {
            strcpy(presult, psource);
            return c;
        }
        c++;
        nLen = p1 - psource;
        memcpy(presult, psource, nLen);
        memcpy(presult + nLen, p_repstr, repstr_leng);
        psource = p1 + searchstr_leng;
        presult = presult + nLen + repstr_leng;
    } while (p1);

    return c;
}

static void
_cdt_cli_response_callback(struct ubus_request *req, int type, blob_attr_t *msg)
{

    pthread_mutex_lock(&mutex);
    LOGD("CLI %s %d\n", __FUNCTION__, __LINE__);
    int rc;
    blob_attr_t *tb[RETURN_MAX];

    LOGD("CLI %s %d\n", __FUNCTION__, __LINE__);
    response_handler_t *_param = (response_handler_t*)(req->priv);

    LOGD("CLI %s %d\n", __FUNCTION__, __LINE__);
    blobmsg_parse(_return_policy, RETURN_MAX, tb, blob_data(msg),
            blob_len(msg));

    if (tb[RETURN_CODE] != NULL) {
        rc = blobmsg_get_u32(tb[RETURN_CODE]);
    } else {
        rc = -1;
    }

    LOGD("rc:%d\n",rc);

    if (tb[RETURN_DATA] != NULL) {
        const char *jsonstring = blobmsg_get_string(tb[RETURN_DATA]);
        if(jsonstring == NULL)
            jsonstring = "E";

        LOGD("jsonstring:%s\n",jsonstring);

        _param->callback(_param->auxiliary, rc, jsonstring);
    } else {
        _param->callback(_param->auxiliary, rc, "cli callback error");
    }
    pthread_mutex_unlock(&mutex);
}

#if 0
    static int
_send_request_command(const char *module, const char *method,
        const char *req, response_handler_t _param)
{
    uint32_t id;
    LOGD("");
    int ret = 0;
    int idx = 0;
    struct blob_buf *tmp = NULL;

    if (_ubus_context == NULL) {
        LOGE("_ubus_context is null\n");
        return -1;
    }


    ret = ubus_lookup_id(_ubus_context, module, &id);
    LOGD("");
    if (ret) {
        LOGE("Failed to look up test object - %s, module:%s\n",
                method, module);
        return ret;
    }

    pthread_mutex_lock(&mutex);
    tmp = &_blob_buf[_blob_buf_idx++ % 20];
    pthread_mutex_unlock(&mutex);

    blob_buf_init(tmp, 0);
    blobmsg_add_string(tmp, METHOD_ARG1, req);
    LOGD("%s %d ubus_invoke\n", __FUNCTION__, __LINE__);
    if (strstr(method, "format") == NULL) {
        LOGD(" ubus_invoke 1\n");
        ret = ubus_invoke(_ubus_context, id, method, tmp->head,
                _cdt_cli_response_callback, &_param, 100*1000);
    } else {
        LOGD(" ubus_invoke 2\n");
        ret = ubus_invoke(_ubus_context, id, method, tmp->head,
                _cdt_cli_response_callback, &_param, 1000*1000);
    }
    return ret;
}

#else
static int
_send_request_command(const char *module, const char *method,
        const char *req, response_handler_t _param, unsigned int timeout)
{
    uint32_t id;
    int ret = 0;
    struct blob_buf tmp;

    if (_ubus_context == NULL) {
        LOGE("_ubus_context is null\n");
        return -1;
    }


    ret = ubus_lookup_id(_ubus_context, module, &id);
    if (ret) {
        LOGE("Failed to look up test object - %s, module:%s\n",
                method, module);
        return ret;
    }

    LOGD("%s %d ubus_invoke\n", __FUNCTION__, __LINE__);
    blob_buf_init(&tmp, 0);
    LOGD("%s %d ubus_invoke\n", __FUNCTION__, __LINE__);
    blobmsg_add_string(&tmp, METHOD_ARG1, req);
    LOGD("%s %d ubus_invoke\n", __FUNCTION__, __LINE__);
    ret = ubus_invoke(_ubus_context, id, method, tmp.head,
                _cdt_cli_response_callback, &_param, timeout);
    return ret;
}
#endif

#define M 1
#if M
static void
_ubus_add_fd()
{
    LOGD("%s %d reconnect add \n", __FUNCTION__, __LINE__);
    if (_ubus_context) {
        ubus_add_uloop(_ubus_context);
    }
}

static void
ubus_reconn_timer(struct uloop_timeout *timeout)
{
    static struct uloop_timeout retry =
    {
        .cb = ubus_reconn_timer,
    };

    int t = 1;

    LOGD("%s %d \n", __FUNCTION__, __LINE__);

    if (_ubus_context) {
        if (ubus_reconnect(_ubus_context, UBUSD_SOCKET_PATH) != 0) {
            uloop_timeout_set(&retry, t * 1000);
            return;
        }
    } else {
        LOGE("%s %d _ubus_context null\n", __FUNCTION__, __LINE__);
    }

   _ubus_add_fd();
}

#endif

static void
_ubus_connection_lost(struct ubus_context *_context)
{
#if M
    ubus_reconn_timer(NULL);
#endif
    return;
}


    static void
_ubus_probe_device_event(struct ubus_context *context,
        struct ubus_event_handler *ev, const char *type, blob_attr_t *msg)
{
    char *str = NULL;

    if (!msg) {
        return;
    }

    str = blobmsg_format_json(msg, true);
    LOGI("{ \"%s\": %s }\n", type, str);
    _event_callback(type, str);
    free(str);
}


    int
cdt_cli_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        int nevents, event_callback cb)
{
    int ret = 0;
    int i = 0;

    if (_event_callback ==  NULL) {
        _event_callback = cb;
    } else {
        LOGE("cdt_cli_register_events has been called before,"
                "only called once in the whole process lifecycle.");
        return -1;
    }

    memset(&_listerner, 0, sizeof(_listerner));
    _listerner.cb = _ubus_probe_device_event;

    for (i=0; i < nevents; i++) {
        if (events[i][0] == 0) {
            LOGD("start register event:%s skip\n",events[i]);
            continue;
        }

        LOGI("tangss register event:%s\n",events[i]);
        ret = ubus_register_event_handler(_ubus_context, &_listerner, events[i]);
        if (ret) {
            LOGE("start register event error :%s",events[i]);
            return -1;
        }
    }

    if (_ubus_context) {
        ubus_add_uloop(_ubus_context);
        uloop_run();
    }
    uloop_done();

    return 0;
}


    int
cdt_cli_send_event(const char *event, const char *content)
{
#if 1 // system call version
#ifdef DEBUG
    char *format = "../../bin/hzbus send -s %s %s \'{\"rc\":0, \"data\":\"%s\"}\'";
#else
    char *format = "hzbus send -s %s %s \'{\"rc\":0, \"data\":\"%s\"}\'";
#endif

    char buf[20480] = {0};
    if (event == NULL) {
        return -1;
    }

    if (content == NULL) {
        content  = "";
    }

    sprintf(buf, format, UBUSD_SOCKET_PATH, event, content);
    buf[20479] = 0;
    LOGD("event buf command:%s", buf);

    system(buf);

    return 0;
#else
    pid_t pid;
    int   rval;

    if (event == NULL) {
        return -1;
    }

    if (!pid) {

        uloop_done();

        uloop_init();

        _ubus_context = ubus_connect(UBUSD_SOCKET_PATH);
        if (!_ubus_context)
        {
            printf("ubus connect failed\n");
            return -1;
        }


        blob_buf_init(&_blob_event, 0);
        blobmsg_add_u32(&_blob_event, "rc", 0);
        blobmsg_add_string(&_blob_event, "data",
                content);
        rval = ubus_send_event(_ubus_context, event,
                _blob_event.head);
        uloop_done();
        if (_ubus_context) {
            ubus_free(_ubus_context);
        }

        return 0;
    } else {

        return 0;
    }
#endif
}


int
cdt_cli_start(void)
{
       signal(SIGPIPE, SIG_IGN);
       signal(SIGCHLD, SIG_IGN);
       signal(SIGTERM, SIG_IGN);
       signal(SIGINT,  SIG_IGN);
       signal(SIGSEGV, SIG_IGN);

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        LOGE("pthread_mutex_init error");
        return 0;
    }
    uloop_init();
    LOGI("%s\n ",UBUSD_SOCKET_PATH);

    errno = 0;
    _ubus_context = ubus_connect(UBUSD_SOCKET_PATH);
    if (!_ubus_context) {
        LOGE("Failed to connect to ubus errno:%d\n",errno);
        uloop_end();
        uloop_done();
        pthread_mutex_destroy(&mutex);
        return -1;
    }

    _ubus_context->connection_lost = _ubus_connection_lost;

    return 0;
}


    int
cdt_cli_stop(void)
{
    uloop_done();
    uloop_end();

    if (_ubus_context) {
        ubus_free(_ubus_context);
        _ubus_context = NULL;
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

int
exec(const char *command, char *with_result, int *with_result_len)
{

    char *cmd = NULL;
    int   len = 0;
    int   max_result = 0;
    FILE *fp = NULL;

    char  read_buf[MAX_RESULT_BUFFER]={0};

    max_result = *with_result_len;

    len = strlen(command) + 20;
    cmd = (char*)malloc(len);
    memset(cmd, 0, len);
    memmove(cmd, command, strlen(command));

    strcat(cmd," 1>&1 2>&1");

    fp = popen(cmd, "r");

    if( fp <=0 )
    {
        free(cmd);
        return 1;
    }

    len = 0;
    while (fgets(read_buf, sizeof(read_buf), fp) > 0) {
        len += strlen(read_buf);
        if (len >= max_result - 1) {
            continue;
        }
        strcat(with_result, read_buf);
    }

    *with_result_len = len;

    pclose(fp);
    free(cmd);

    return 0;
}

int
cdt_cli_request_timeout(response_handler_t param, const char *module,
        const char *method, const char *content, unsigned int timeout)
{
    if (!module  || !method || !content) {
        LOGE("param error\n");
        return -1;
    }

    if (!strcmp(method, "format") || !strcmp(method, "getdisksinfo")) {
    //if (1) { //tangss
            char cmd[1024] = {0};
            int  rval      =  0;

            int  reslt_len                 = MAX_RESULT_BUFFER;
            char reslt[MAX_RESULT_BUFFER]  = {0};
            char reslt1[MAX_RESULT_BUFFER] = {0};

            if (!strcmp(method, "format")) {
                sprintf(cmd, "hzbus -s %s -t 1000 call %s %s \'%s\'",
                    UBUSD_SOCKET_PATH, module, method, content);
            } else {
                sprintf(cmd, "hzbus -s %s -t 600 call %s %s \'%s\'",
                UBUSD_SOCKET_PATH, module, method, content);
            }
            LOGE("cmd:---->%s\n", cmd);
            rval = exec(cmd, reslt, &reslt_len);
            if (rval) {
                LOGE("%s %d ", __FILE__, __LINE__);
                if (param.callback != NULL) {
                    param.callback(param.auxiliary, rval, "cli callback error");
                }
            } else {
                if (param.callback != NULL) {
                    str_replace(reslt1, reslt, "\\n", "");
                    //memset(reslt, 0, sizeof(reslt));
                    //str_replace(reslt, reslt1, "\\", "");
                    param.callback(param.auxiliary, rval, reslt1);
                }
            }


            return rval;
    } else {
        return _send_request_command(module, method, content, param, timeout);
    }
}

int
cdt_cli_request(response_handler_t param, const char *module,
        const char *method, const char *content)
{
    return cdt_cli_request_timeout(param, module, method, content,
            DEFAULT_CDT_REQUEST_TIMETOUT);
}
