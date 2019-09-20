/*
 * conduit client
 * ipc call , sent/receive events
 * 1\call sequence:
 * cdt_cli_start (call once)
 * cdt_cli_request
 * cdt_cli_stop (call once)
 *
 * 2\receive events sequence:
 * cdt_cli_start (call once)
 * define function event_callback
 * cdt_cli_register_events (call once)
 * cdt_cli_stop (call once)
 *
 * 3\send event sequence:
 * cdt_cli_start (call once)
 * cdt_cli_send_event
 * cdt_cli_stop (call once)
 *
 * note that: functions as following called once in the whole process lifecycle
 * cdt_cli_start
 * cdt_cli_stop
 * cdt_cli_register_events
 */
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
#define COLOR_INFO    "32;40;1m"
#define COLOR_DEBUG   "36;40;1m"
#define COLOR_TRACE   "37;40;1m"

#define Msg_Info(format, args...) (printf( ESC_START COLOR_INFO \
        "[INFO]-[%s]-[%d]:" format ESC_END,  __FUNCTION__ , __LINE__, ##args))
// #define Msg_Debug(format, args...)

#define Msg_Debug(format, args...) (printf( ESC_START COLOR_DEBUG \
        "[DEBUG]-[%s]-[%d]:" format ESC_END "\n", __FUNCTION__ , __LINE__, ##args))
#define Msg_Warn(format, args...) (printf( ESC_START COLOR_WARN \
        "[WARN]-[%s]-[%d]:" format ESC_END "\n",  __FUNCTION__ , __LINE__, ##args))
#define Msg_Error(format, args...) \
    (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" \
             format ESC_END "\n", __FUNCTION__ , __LINE__, ##args))

#define Msg_Info_L(format, args...) \
    (printf( ESC_START COLOR_INFO "[INFO]-[%s]-[%s]-[%d]:" format ESC_END "\n", \
         __FILE__, __FUNCTION__ , __LINE__, ##args))

#define Msg_Debug_L(format, args...) \
    (printf( ESC_START COLOR_DEBUG "[DEBUG]-[%s]-[%s]-[%d]:" \
             format ESC_END, __FILE__, __FUNCTION__ , __LINE__, ##args))

#define Msg_Warn_L(format, args...) \
    (printf( ESC_START COLOR_WARN "[WARN]-[%s]-[%s]-[%d]:" format ESC_END, \
             __FILE__, __FUNCTION__ , __LINE__, ##args))

#define Msg_Error_L(format, args...) \
    (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%s]-[%d]:" format ESC_END, \
             __FILE__, __FUNCTION__ , __LINE__, ##args))
#endif

#define MAX_EVENTS      8
#define MAX_EVENT_LEN   64


typedef void (*response_callback)(void *auxiliary, int resp_code,
        const char *resp_content);

typedef void (*event_callback)(const char *event, const char *resp_content);

#ifndef CUSTOM_SYNC_PARAM_STRUCT
#define CUSTOM_SYNC_PARAM_STRUCT
typedef struct {
	response_callback  callback;

    //auxiliary is not sent out, and when the responded as an argument of
    //response function, refer to the response_callback.it's recommended NULL, 
    //if not sure.
	void              *auxiliary;
}response_handler_t;
#endif

//called once in the whole process lifecycle
int cdt_cli_start(void);

int cdt_cli_request(response_handler_t param, const char *module,
        const char *method, const char *content);

//register events only called once in the whole process lifecycle
//const char *events ={"sdcard","usbin","usbout"}
int	cdt_cli_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        event_callback callback);
int	cdt_cli_send_event(const char *event, const char *content);

int cdt_cli_stop(void);

#endif
