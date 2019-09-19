#include <unistd.h>
#include <signal.h>

#include <libubox/blobmsg_json.h>
#include "libubus.h"
#include "count.h"
#include "ubus_server_command.h"
#include "ubus_app_error.h"

//socket
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>

#include "conduit.h"
#include <pthread.h>

#if DEBUG
// normal_sync_call(const char* content);

static int callback(const char* c)
{
	printf("test_server_main %s \n",c);
	return 0;
}
normal_sync_callback_func _func = &callback;

static int sta_stream(int type, int devid, push_buffer fun_push_buffer)
{
	printf("%s %d type:%d devid:%d \n", __FUNCTION__, __LINE__, type, devid);
	return 0;
}

static int sto_stream(int type, int devid)
{
	printf("%s %d type:%d devid:%d \n", __FUNCTION__, __LINE__, type, devid);
	return 0;
}

int main(int argc, char **argv)
{	
	set_normal_sync_callback(_func);
	start_conduit();
	set_stream_callback(&sta_stream, &sto_stream);
	while(1)
		sleep(1);
	stop_conduit();
	return 0;
}
#endif
