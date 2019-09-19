
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

#include "libubus.h"
#include "conduit_common.h"
#include "conduit_client.h"

//#include "count.h"
//#include "ubus_app_error.h"
//#include "ubus_server_command.h"

#define debug 0

enum {
	RETURN_CODE,
	RETURN_DATA,
	RETURN_MAX,
};

static	pthread_t _pid = -1;

static struct ubus_context *_ubus_context;
static struct ubus_event_handler _listerner;
static struct blob_buf _blob_buf;

static event_callback _event_callback;

static const struct blobmsg_policy _return_policy[RETURN_MAX] = {
	[RETURN_CODE] = { .name = "rc", .type = BLOBMSG_TYPE_INT32 },
	[RETURN_DATA] = { .name = "data", .type = BLOBMSG_TYPE_STRING },
};

static void
_cdt_cli_request_callback(struct ubus_request *req, int type,
        struct blob_attr *msg)
{
	int rc;
	struct blob_attr *tb[RETURN_MAX];

	request_param_t *_param = (request_param_t*)(req->priv);

	blobmsg_parse(_return_policy, RETURN_MAX, tb, blob_data(msg),
            blob_len(msg));

	rc = blobmsg_get_u32(tb[RETURN_CODE]);
	Msg_Debug("rc:%d \n",rc);

	const char *jsonstring = blobmsg_get_string(tb[RETURN_DATA]);
	if(jsonstring == NULL)
		jsonstring = "E";

	Msg_Debug("jsonstring:%s \n",jsonstring);

	_param->callback(_param->data, rc, jsonstring);
}

static int
_send_request_command(const char *module, const char *method,
        const char *jsonstring, request_param_t _param)
{
	uint32_t id;
	int ret = ubus_lookup_id(_ubus_context, module, &id);
	if (ret) {
		Msg_Error("Failed to look up test object - %s, module:%s \n",
                method, module);
		return ret;
	}

	blob_buf_init(&_blob_buf, 0);
	blobmsg_add_string(&_blob_buf, HZCUSTOM_METHOD_ARG1, jsonstring);
	Msg_Debug("ubus_invoke \n");
	return ubus_invoke(_ubus_context, id, method, _blob_buf.head,
            _cdt_cli_request_callback, &_param, 3000);
}


static void
_ubus_connection_lost(struct ubus_context *_context)
{
	// ubus_reconn_timer(NULL);
    return;
}


static void
_ubus_probe_device_event(struct ubus_context *context,
        struct ubus_event_handler *ev, const char *type, struct blob_attr *msg)
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
_ubus_uloop_thread(void *argv)
{
	if (_ubus_context) {
		ubus_add_uloop(_ubus_context);
		uloop_run();
	} else {
		Msg_Error("_ubus_context is NULL\n");
    }

	return NULL;
}


int
cdt_cli_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
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

	for (i=0; i<8; i++) {
		if (events[i][0] == 0) {
			Msg_Debug("start register event:%s skip \n",events[i]);
			continue;
		}

		Msg_Info("tangss register event:%s\n",events[i]);
		ret = ubus_register_event_handler(_ubus_context, &_listerner, events[i]);
		if (ret) {
			Msg_Error("start register event error :%s",events[i]);
		}
	}

	if (_pid == -1) {
		int err = pthread_create(&_pid, NULL, _ubus_uloop_thread, NULL);
		if (err != 0) {
			Msg_Error("exit, as can't create thread 1: %s\n", strerror(err));
			exit(-1);
		}
		//Msg_Error("create thread _pid:%d\n",(int)_pid);
	}

	return 0;
}


int
cdt_cli_send_event(const char *event, const char *jsonstring)
{
	if (event == NULL) {
        return -1;
    }

    blob_buf_init(&_blob_buf, 0);
    blobmsg_add_u32(&_blob_buf, "rc", 0);
    blobmsg_add_string(&_blob_buf, "data", jsonstring);

    return ubus_send_event(_ubus_context, event, _blob_buf.head);
}


int
cdt_cli_start(void)
{
	signal(SIGPIPE, SIG_IGN);

	uloop_init();
	Msg_Info("%s \n ",UBUSD_SOCKET_PATH);

	errno = 0;
	_ubus_context = ubus_connect(UBUSD_SOCKET_PATH);
	if (!_ubus_context) {
		Msg_Error("Failed to connect to ubus errno:%d\n",errno);
		uloop_done();
		return -1;
	}

	_ubus_context->connection_lost = _ubus_connection_lost;

	return 0;
}


int
cdt_cli_stop(void)
{
	if (_ubus_context) {
		uloop_done();
		ubus_free(_ubus_context);
		_ubus_context = NULL;
	}

	return 0;
}


int
cdt_cli_request(request_param_t param, const char *module,
        const char *method, const char *content)
{
	return _send_request_command(module,method,content,param);
}

