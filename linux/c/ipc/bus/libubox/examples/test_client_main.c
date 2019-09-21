
#include <sys/time.h>
#include <unistd.h>

#include <libubox/ustream.h>

#include <libubox/blobmsg_json.h>
#include "libubus.h"
#include "count.h"
#include "ubus_app_error.h"
//socket
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>  
#include "conduit_client.h"


#ifndef _DEBUGLOG_H
#define _DEBUGLOG_H
 
#define ESC_START     "\033["
#define ESC_END       "\033[0m"
#define COLOR_FATAL   "31;40;5m"
#define COLOR_ALERT   "31;40;1m"
#define COLOR_CRIT    "31;40;1m"
#define COLOR_ERROR   "31;40;1m"
#define COLOR_WARN    "33;40;1m"
#define COLOR_NOTICE  "34;40;1m"
#define COLOR_INFO    "32;40;1m"
#define COLOR_DEBUG   "36;40;1m"
#define COLOR_TRACE   "37;40;1m"
 
#define Msg_Info(format, args...) (printf( ESC_START COLOR_INFO "[INFO]-[%s]-[%d]:" format ESC_END,  __FUNCTION__ , __LINE__, ##args))
#define Msg_Debug(format, args...) (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn(format, args...) (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%d]:" format ESC_END,  __FUNCTION__ , __LINE__, ##args))
#define Msg_Error(format, args...) (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args))

#define Msg_Info_L(format, args...) (printf( ESC_START COLOR_INFO "[INFO]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Debug_L(format, args...) (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn_L(format, args...) (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Error_L(format, args...) (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))

#endif

#if DEBUG

static void _buffer_reciver(const char* buffer,const int len)
{
	printf("_buffer_reciver %s len:%d \n",buffer,len);
}
buffer_reciver gbr = &_buffer_reciver;

static void _sync_callback(int rc, const char* content)
{
	printf("_buffer_reciver %02x rc:%d \n",content[0],rc);
}
int main(int argc, char **argv)
{
	Msg_Info("\n");
	set_normal_sync_callback(&_sync_callback);
	Msg_Info("\n");
	start_conduit();
	Msg_Info("\n");
	normal_sync_call("{\"data\":{\"d\":2}}");
	start_stream(1, 0, gbr);
	Msg_Info("\n");

	while(1)
		sleep(1);
	Msg_Info("\n");
	stop_conduit();
	return 0;
}
#else
#endif