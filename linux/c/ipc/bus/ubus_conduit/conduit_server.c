
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <errno.h>

#include <libubox/blobmsg_json.h>

#include "libubus.h"
#include "conduit_common.h"
#include "conduit_server.h"

//#include "count.h"
//#include "ubus_server_command.h"
//#include "ubus_app_error.h"

#ifndef MAX_UNIXPATH_LEN
#define MAX_UNIXPATH_LEN 128
#endif

#ifndef MAX_SOCKET_BUF_LEN
#define MAX_SOCKET_BUF_LEN 10240 //10k
#endif
#ifndef MAX_RETRIES
#define MAX_RETRIES 10
#endif

typedef struct blob_buf             blob_buf_t;
typedef struct blob_attr            blob_attr_t;
typedef struct ubus_object          ubus_object_t;
typedef struct ubus_method          ubus_method_t;
typedef struct ubus_context         ubus_context_t;
typedef struct blobmsg_policy       blobmsg_policy_t;
typedef struct ubus_object_type     ubus_object_type_t;
typedef struct ubus_request_data    ubus_request_data_t;
typedef struct ubus_event_handler   ubus_event_handler_st;

enum {
	MY_DATA,
	_MY_MAX,
};

enum
{
	UBUS_APP_ERROR_BASE=-100,

	UBUS_APP_ERROR_INTERNAL_NULLPOINTER,
	UBUS_APP_ERROR_PARSEREQ,
	UBUS_APP_ERROR_SUB_NOTFOUND,
	UBUS_APP_ERROR_INTERNAL_PROCESSCMD,
	UBUS_APP_ERROR_INTERNAL_FD,
	UBUS_APP_ERROR_INTERNAL_SOCKET,
	UBUS_APP_ERROR_INTERNAL_OVERRANGE,
	UBUS_APP_ERROR_IEMPTY_NPUT_METHODS,
	UBUS_APP_ERROR_EXISTED,
	UBUS_APP_ERROR_NOIDLE,

	UBUS_APP_OK=0,
};

static pthread_t       _ubus_loop_tid = -1;
static ubus_context_t *_ctx;
static blob_buf_t      _buf;
static blob_buf_t      event_buf;

static const blobmsg_policy_t policies[] =
    {[MY_DATA] = {.name="data", .type = BLOBMSG_TYPE_STRING},};

static const int methods_max = MAX_OBJECTS * MAX_METHODS;

typedef struct {
	const char	key[MAX_METHOD_NAME_LEN+MAX_OBJ_NAME_LEN];
	const char 	method_name[MAX_METHOD_NAME_LEN];
	request_callback 	fun;
} method_t;

static method_t _methods[MAX_OBJECTS * MAX_METHODS];
static ubus_event_handler_st _listerner;
static event_callback _event_callback;

static void
_reply_int(ubus_context_t *_ctx, ubus_request_data_t *req, int ret,
        const char* datajson)
{
	blob_buf_init(&_buf, 0);
	blobmsg_add_u32(&_buf, "rc", ret);
	if (datajson != NULL) {
		blobmsg_add_string(&_buf, "data", datajson);
    }

	ubus_send_reply(_ctx, req, _buf.head);
}


static int
_response(ubus_context_t *_ctx, ubus_object_t *obj, ubus_request_data_t *req,
        const char *method, blob_attr_t *msg)
{
	Msg_Debug(" START method:%s\n",method);

	int   len = 0;
	int   rc = 0;
    int   i = 0;
	char *str = NULL;

	char retstr[MAX_RESULT_BUFFER_SIZE] = {0};
	char tmpstr[MAX_RESULT_BUFFER_SIZE] = {0};

	blob_attr_t *tb[_MY_MAX];

	Msg_Debug("START msg:%s msglen:%d\n",(char*)blob_data(msg),blob_len(msg));
	blobmsg_parse(policies, _MY_MAX, tb, blob_data(msg), blob_len(msg));
	Msg_Debug("START blobmsg_get_string:%s\n",blobmsg_get_string(msg));

	if (tb[MY_DATA] == NULL) {
		Msg_Error(" START tb[MY_DATA] is NULL\n");
		return UBUS_APP_ERROR_INTERNAL_NULLPOINTER;
	}

	str = blobmsg_get_string(tb[MY_DATA]);
	Msg_Debug("str:%s \n",str);
	if (!str) {
		Msg_Error("blobmsg_get_string error error:%d\n", errno);
		return UBUS_APP_ERROR_PARSEREQ;
	}

	len =  strlen(obj->name);
	memmove(tmpstr, obj->name,len);
	memmove((tmpstr+len), method, strlen(method));

	Msg_Debug("tmpstr:%s \n",tmpstr);

	tmpstr[MAX_RESULT_BUFFER_SIZE-1]=0;
	for(i = 0; i < methods_max; i++)
	{

		Msg_Debug("_methods[i].key:%s --\n",
                _methods[i].key);
		if (!strcmp(_methods[i].key, tmpstr)) {
			rc = _methods[i].fun(str, retstr);
			_reply_int(_ctx, req, rc, retstr);
			break;
		}
	}

	Msg_Debug(" END\n");
	return UBUS_APP_OK;
}


int
cdt_srv_add_module(const char* module_name, module_method_t* module_methods,
        int n_methods)
{
	int   i = 0;
	int   j = -1;
    int   n = -1;
    int   len = -1;
	char *tmp = NULL;
	char  retstr[MAX_RESULT_BUFFER_SIZE]={0};

	ubus_object_type_t *tmptype = NULL;
    ubus_method_t      *methods = NULL;
    ubus_object_t      *object = NULL;

	if (module_name == NULL || module_methods == NULL) {
		return UBUS_APP_ERROR_INTERNAL_NULLPOINTER;
	}

	if (n_methods <= 0) {
		return UBUS_APP_ERROR_IEMPTY_NPUT_METHODS;
	}

	for (j = 0; j < n_methods; j++) {
		n=-1;

		len = strlen(module_name);
		memmove(retstr, module_name, len);
		memmove((retstr+len), module_methods[j].method_name,
                strlen(module_methods[j].method_name));
		retstr[MAX_RESULT_BUFFER_SIZE-1]=0;

		for (i = 0; i < methods_max; i++) {
			if (_methods[i].key[0] == 0 ) {
				if (n < 0){
					n = i;
                }
                break;
			}

			if (!strcmp(_methods[i].key, retstr)) {
				Msg_Debug("%s has been registered, please check mannually!\n",
                        module_name);
				return UBUS_APP_ERROR_EXISTED;
			}
		}

		if (n < methods_max && n >= 0) {
			Msg_Debug("module_methods[j].fun :%p \n", module_methods[j].fun);

			strcpy((char*)(_methods[n].key), retstr);
			strcpy((char*)(_methods[n].method_name),
                    module_methods[j].method_name);
			_methods[n].fun = module_methods[j].fun;
		}
	}

	Msg_Debug("i:%d j:%d custom_objec*t_functions_max:%d, n_methods:%d\n",
            i, j, methods_max, n_methods);

	methods = (ubus_method_t*)malloc(sizeof(ubus_method_t) * n_methods);

    for (i = 0; i < n_methods; i++) {
        j = strlen(module_methods[i].method_name) + 1;
        j = j > MAX_METHOD_NAME_LEN ? MAX_METHOD_NAME_LEN : j;
        tmp = (char* )malloc(j);
        memset(tmp, 0, j);
        memmove(tmp, module_methods[i].method_name, j);

        methods[i].name = tmp;
        methods[i].handler = _response;
        methods[i].policy = policies;
        methods[i].n_policy = ARRAY_SIZE(policies);
    }

	object = (ubus_object_t*)malloc(sizeof(ubus_object_t));

	i = strlen(module_name) + 1;
	i = i > MAX_OBJ_NAME_LEN? MAX_OBJ_NAME_LEN : i;
	Msg_Debug("module_name:%s length :%d\n", module_name,i-1);

	object->name = (char*)malloc(i);
	memset((char*)object->name, 0, i);
	memmove((char*)object->name, module_name, i);

	tmptype = (ubus_object_type_t *)malloc(sizeof(ubus_object_type_t));
	tmptype->name = object->name;
	tmptype->methods = methods;
	tmptype->n_methods = n_methods;
	tmptype->id = 0;

	object->type = tmptype;
	object->methods = methods;
	object->n_methods = n_methods;
	ubus_add_object(_ctx, object);

    /*==================
    static const struct ubus_method test_methods[] = {
        UBUS_METHOD("helloworld", test_hello, hello_policy),
    };

    static struct ubus_object_type test_object_type =
        UBUS_OBJECT_TYPE("test_ubus", test_methods);

    static struct ubus_object test_object = {
        .name = "test_ubus",
        .type = &test_object_type,
        .methods = test_methods,
        .n_methods = ARRAY_SIZE(test_methods)
    };
    //======================================
    */

	return UBUS_APP_OK;

}

int
cdt_srv_del_module(const char* module_name)
{
	return UBUS_APP_OK;
}

static void
_ubus_probe_device_event(ubus_context_t *context,
        ubus_event_handler_st *ev, const char *type, struct blob_attr *msg)
{
	char *str = NULL;

	if (!msg) {
		return;
    }

	str = blobmsg_format_json(msg, true);
	Msg_Info("{ \"%s\": %s }\n", type, str);
	_event_callback(type, str);
	free(str);
}
static void*
_uloop_run_thread(void *arg)
{
	uloop_run();

    Msg_Debug(" QUIT ULOOP TREHAD!!!!!!!");
    //uloop_done();

    pthread_exit(0);
	return NULL;
}

static int
_cdt_srv_run(void)
{
	ubus_add_uloop(_ctx);
	pthread_create(&_ubus_loop_tid, NULL, _uloop_run_thread, NULL);

	return 0;
}

int
cdt_srv_start(void)
{
    int i = 0;
   
	signal(SIGPIPE, SIG_IGN);

	if (_ctx) {
		Msg_Error("has been started! don't call multi-times");
		return -1;
	}

	for (i = 0; i < methods_max; i++) {
		memset((char*)_methods[i].key, 0, sizeof(_methods[i].key));
		memset((char*)_methods[i].method_name, 0,
                sizeof(_methods[i].method_name));
		_methods[i].fun = NULL;
	}

	uloop_init();

	_ctx = ubus_connect(UBUSD_SOCKET_PATH);
	if (!_ctx) {
		Msg_Error("uloop_connect error UBUSD_SOCKET_PATH:%s\n",
                UBUSD_SOCKET_PATH);
		uloop_done();
		return -1;
	}

    _cdt_srv_run();

	return UBUS_APP_OK;
}

//BUG: uloop_run() do not quit after uloop_done & uloop_end when testing by
//cmockery.
int
cdt_srv_stop(void)
{
    int  rval = -1;
    int *exit_code = NULL;

    uloop_done();
    Msg_Debug("");
    uloop_end();
    uloop_done();
    Msg_Debug("");

    if (_ubus_loop_tid > 0) {
        rval = pthread_join(_ubus_loop_tid, (void **)&exit_code);
        printf("%s return:%p\n", __FUNCTION__, exit_code);
    }

    Msg_Debug("");
	if (_ctx) {
        ubus_free(_ctx);
    }
	_ctx = NULL;

    return rval;
}

int
cdt_srv_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        event_callback callback)
{
	int ret = 0;
    int i = 0;

    if (_event_callback ==  NULL) {
 	    _event_callback = callback;
    } else {
        Msg_Error("cdt_cli_register_events has been called before,"
                "only called once in the whole process lifecycle.");
        return -1;
    }
	/* 注册特定event的_listerner。多个event可以使用同一个_listerner */
	memset(&_listerner, 0, sizeof(_listerner));
	_listerner.cb = _ubus_probe_device_event;
	// Msg_Info("register event:%s\n",events[0]);

	for (i = 0; i < MAX_EVENTS; i++) {
		if (events[i][0] == 0) {
			Msg_Debug("start register event:%s skip \n",events[i]);
			continue;
		}

		Msg_Info("register event:%s\n",events[i]);
		ret = ubus_register_event_handler(_ctx, &_listerner, events[i]);
		if (ret) {
			Msg_Error("start register event error :%s",events[i]);
		}
	}

	return 0;
}

int
cdt_srv_send_event(const char *event, const char *content)
{
    blob_buf_init(&event_buf, 0);
	blobmsg_add_u32(&event_buf, "rc", 0);
	blobmsg_add_string(&event_buf, "data", content);

	return ubus_send_event(_ctx, event, event_buf.head);
}

