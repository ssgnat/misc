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


//#endif

#define LOG_TAG "CDT_CLI_SO"

#ifndef ESC_START
#define ESC_START
#endif

#ifndef ESC_END
#define ESC_END
#endif

#ifndef COLOR_ERROR
#define COLOR_ERROR
#endif

#ifndef COLOR_INFO
#define COLOR_INFO
#endif

#ifndef COLOR_WARN
#define COLOR_WARN
#endif

#ifndef COLOR_DEBUG
#define COLOR_DEBUG
#endif

#ifdef DEBUG
    #ifdef ANDROID
        #include <android/log.h>
        #define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
        #define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
        #define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__))
        #define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))
    #else
        #define LOGI(format, args...) (printf( ESC_START COLOR_INFO \
            "[INFO]-[%s]-[%d]:" format ESC_END,  __FUNCTION__ , __LINE__, ##args))
        #define LOGD(format, args...) (printf( ESC_START COLOR_DEBUG \
            "[DEBUG]-[%s]-[%d]:" format ESC_END "\n", __FUNCTION__ , __LINE__, ##args))
        #define LOGW(format, args...) (printf( ESC_START COLOR_WARN \
            "[WARN]-[%s]-[%d]:" format ESC_END "\n",  __FUNCTION__ , __LINE__, ##args))
        #define LOGE(format, args...) \
        (printf( ESC_START COLOR_ERROR "[ERROR]-[%s]-[%d]:" \
             format ESC_END "\n", __FUNCTION__ , __LINE__, ##args))

    #endif
#else
    #define LOGD(...) NOT ANDROID ? PLEASE RELEASE ME;
    #define LOGI(...);
    #define LOGW(...);
    #define LOGE(...);
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

int cdt_cli_request_timeout(response_handler_t param, const char *module,
        const char *method, const char *content, unsigned int timeout);

int cdt_cli_request(response_handler_t param, const char *module,
        const char *method, const char *content/*,unsigned int timetout = 5000*/);

//register events only called once in the whole process lifecycle
//const char *events ={"sdcard","usbin","usbout"}
int	cdt_cli_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        int nevents, event_callback callback);
int	cdt_cli_send_event(const char *event, const char *content);

int cdt_cli_stop(void);

#endif
