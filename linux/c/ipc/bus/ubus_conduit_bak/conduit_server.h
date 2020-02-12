#ifndef _CONDUIT_SRV_H_
#define _CONDUIT_SRV_H_

#define DEBUG
#define ANDROID_PLATFORM

#define LOG_TAG "CDT_SRV_SO"

#ifdef DEBUG
    #ifdef ANDROID_PLATFORM
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


#define MAX_RESULT_BUFFER_SIZE 20480

#define MAX_OBJECTS 8
#define MAX_METHODS 16
#define MAX_OBJ_NAME_LEN 32
#define MAX_METHOD_NAME_LEN 32

#define MAX_EVENTS 8
#define MAX_EVENT_LEN 64

typedef void (*event_callback)(const char *event_type, const char *resp_content);

typedef int (*request_callback)(const char *req_content,
        char resp_content[MAX_RESULT_BUFFER_SIZE]);

typedef struct {
	char method_name[MAX_METHOD_NAME_LEN];
	request_callback fun;
} module_method_t;


int cdt_srv_start(void);

int cdt_srv_add_module(const char *module_name,
        module_method_t *module_methods, int n_methods);

int cdt_srv_send_event(const char *event_type, const char *event_content);
int cdt_srv_register_events(const char events[MAX_EVENTS][MAX_EVENT_LEN],
        int nevents, event_callback callback);

int cdt_srv_run(void);
int cdt_srv_stop(void);
#endif
