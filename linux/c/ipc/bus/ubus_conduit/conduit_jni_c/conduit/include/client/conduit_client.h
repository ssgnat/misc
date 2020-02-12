#ifndef _CONDUIT_CLIENT_H_
#define _CONDUIT_CLIENT_H_


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
#define COLOR_INFO    "32;40;1m" #define COLOR_DEBUG   "36;40;1m"
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

#define MAX_BUFFER_LEN 102400

enum
{
	VIDEO,
	AUDIO,
	INVALID,
};

int  start_conduit();

typedef void (*normal_sync_callback_func)(int rc, const char* content);
typedef void (*custom_sync_callback_func)(void* data, int rc, const char* content);
typedef void (*buffer_reciver)(const int type, const int devid, const char* buffer,const int len);

void start_stream(int type, int devid, buffer_reciver _stream_callback);
void stop_stream(int type,int devid);

int  normal_sync_call(const char* moudle, const char* method, const char* content,normal_sync_callback_func _func);

#ifndef CUSTOM_SYNC_PARAM_STRUCT
#define CUSTOM_SYNC_PARAM_STRUCT
typedef struct _custom_sync_param_struct
{
	custom_sync_callback_func _func;
	void* data; // callback passthrought data
}custom_sync_param;
#endif

int  custom_sync_call_with(custom_sync_param _param, const char* moudle,const char* method, const char* content);
typedef void (*event_callback)(const char* type, const char* str);
//const char* events
// ={"sdcard","usbin","usbout"}
int	client_ubus_register_events(const char events[8][64], event_callback _event_callback);
int	client_ubus_send_events(const char* event, const char* jsonstring);

int  stop_conduit();

#endif
