#ifndef _CONDUIT_SRV_H_
#define _CONDUIT_SRV_H_

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

#define Msg_Info(format, args...) \
    (printf( ESC_START COLOR_INFO "[INFO]-[%s]-[%d]:" format ESC_END "\n",   \
             __FUNCTION__ , __LINE__, ##args))
#define Msg_Debug(format, args...) \
    (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%d]:" format ESC_END "\n", \
             __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn(format, args...) \
    (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%d]:" format ESC_END "\n",   \
             __FUNCTION__ , __LINE__, ##args))
#define Msg_Error(format, args...) \
    (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" format ESC_END "\n", \
             __FUNCTION__ , __LINE__, ##args))
#endif

#define MAX_RESULT_BUFFER_SIZE 256

//#############################CUSTOM BEGIN####################################
#define CUSTOM_OBJECT_NAME_LEN_MAX 2048 //2k
//custom hzbus process function prototype

#define MAX_OBJECTS 4
#define MAX_METHODS 4
#define MAX_OBJ_NAME_LEN 16
#define MAX_METHOD_NAME_LEN 16

#define MAX_EVENTS 8
#define MAX_EVENT_LEN 64

typedef void (*event_callback)(const char *event_type, const char *resp_content);

typedef int (*request_callback)(const char *req_content,
        char resp_content[CUSTOM_OBJECT_NAME_LEN_MAX]);

typedef struct {
	char method_name[MAX_METHOD_NAME_LEN];
	request_callback fun;
} module_method_t;


int cdt_srv_start(void);

int cdt_srv_add_module(const char *module_name,
        module_method_t *module_methods, int n_methods);

int cdt_srv_send_event(const char *event_type, const char *event_content);
int cdt_srv_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        event_callback callback);

int cdt_srv_stop(void);
#endif
