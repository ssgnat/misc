#ifndef _CONDUIT_H_
#define _CONDUIT_H_

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
// #define Msg_Debug(format, args...)
#define Msg_Debug(format, args...) (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn(format, args...) (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%d]:" format ESC_END,  __FUNCTION__ , __LINE__, ##args))
#define Msg_Error(format, args...) (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" format ESC_END, __FUNCTION__ , __LINE__, ##args))
#define Msg_Info_L(format, args...) (printf( ESC_START COLOR_INFO "[INFO]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Debug_L(format, args...) (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn_L(format, args...) (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#define Msg_Error_L(format, args...) (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%s]-[%d]:" format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))
#endif

#define MAX_RESULT_BUFFER_SIZE 256

//#############################CUSTOM BEGIN##############################################
#define CUSTOM_OBJECT_NAME_LEN_MAX 2048 //2k
//custom hzbus process function prototype
typedef int (*_hzbus_custom_process_func)(const char* request, char result[CUSTOM_OBJECT_NAME_LEN_MAX]); 

#ifndef CUSTOM_OBJECTNAME_LEN_MAX
#define CUSTOM_OBJECTNAME_LEN_MAX 16
#endif
#ifndef CUSTOM_METHODNAME_LEN_MAX
#define CUSTOM_METHODNAME_LEN_MAX 16
#endif

#ifndef CUSTOM_OBJECT_NUM_MAX
#define CUSTOM_OBJECT_NUM_MAX 4
#endif

#ifndef CUSTOM_METHOD_NUM_MAX
#define CUSTOM_METHOD_NUM_MAX 4
#endif

struct hzbus_method
{
	char method_name[CUSTOM_METHODNAME_LEN_MAX];
	_hzbus_custom_process_func _fun;
};

int add_conduit_custom_object(const char* objectname, struct hzbus_method* hzbus_methods, int n_methods);
int del_conduit_custom_object(const char* objectname);

//#############################CUSTOM END################################################
int 	init_conduit();

// //
// typedef int (*_start_stream)(int type, int devid, push_buffer fun_push_buffer);
// typedef int (*_stop_stream)(int type, int devid);
// int 	set_stream_callback(int type, _start_stream _start, _stop_stream _stop);

typedef int (*normal_sync_callback_func)(const char* request, char result[MAX_RESULT_BUFFER_SIZE]); 
void 	set_normal_sync_callback(normal_sync_callback_func _sync_call);

int 	run_conduit();

int 	server_ubus_send_event(int type, int devid, const char* event, const char* jsonstr);

int 	stop_conduit();
#endif
