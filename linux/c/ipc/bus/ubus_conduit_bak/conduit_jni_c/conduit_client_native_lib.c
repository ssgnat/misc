#include "conduit_client.h"
#include <jni.h>
#include <stdio.h>
#include <string.h>
#include <android/log.h>

#define TAG    "CONDUIT_JNI_C"
#define CLASS_NATIVE_PATH "com/horzon/conduit/mynative/conduit"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)

#ifdef LOG_REDIRECT_FILE
#define TEMPORARY_LOG_FILE "/mnt/sdcard/log.txt"
#define LOG_REDIRECT() \
    freopen(TEMPORARY_LOG_FILE, "a", stdout); setbuf(stdout, NULL); \
    freopen(TEMPORARY_LOG_FILE, "a", stderr); setbuf(stderr, NULL);
#else
#define LOG_REDIRECT() ;

#endif


static JavaVM *g_jvm;
static jclass conduit_class_clazz;

static JNIEnv *env_normal_callback_thread = NULL;
static JNIEnv *g_jnienv = NULL;
static jobject m_object;
static jclass m_clazz;
static jmethodID m_stream_push_buffer_method_id;
static jmethodID resp_callback_mid;
static jmethodID event_callback_mid;
static jbyteArray buffer_data = NULL;
static int buffer_status = 0;

static void _event_callback(const char* type, const char* str);
static event_callback g_event_callback = &_event_callback;

#define MAX_EVENTS_NUM 16
#define MAX_EVENT_LEN 64
#define MAX_CUSTOME_METHOD_NUM 20
static char _events[MAX_EVENTS_NUM][MAX_EVENT_LEN];


static void
_response_callback(void* _auxiliary, int rc, const char* content)
{
    char tmp[256]="E";
    int i = 0;

    LOGD("%s %d content:%s \n",__FUNCTION__, __LINE__, content);

    if(content) {
        memmove(tmp,content,256);
    }

    JNIEnv *env = g_jnienv;
    (*g_jvm)->AttachCurrentThread(g_jvm, &env, NULL);
    jstring jstr_content = (*env)->NewStringUTF(env, content);
    jstring jstr_auxiliary = (*env)->NewStringUTF(env, _auxiliary);

    (*env)->CallStaticVoidMethod
        (env, m_clazz, resp_callback_mid, rc, jstr_content, jstr_auxiliary);

    (*env)->DeleteLocalRef(env, jstr_content);
    (*env)->DeleteLocalRef(env, jstr_auxiliary);
    // (*g_jvm)->DetachCurrentThread(g_jvm);
}

JNIEXPORT void JNICALL
    Java_com_horzon_conduit_mynative_conduit_start
        (JNIEnv *env, jobject instance) {

            int rval = 0;
    LOG_REDIRECT();

    g_jnienv = env;
    const char *str_resp_callback = "async_callback";
    const char *str_event_callback_method = "event_callback";

    LOGD("str_event_callback_method_ %s", str_event_callback_method);

    (*env)->GetJavaVM(env,&g_jvm);
    jclass jclassRef = (*env)->FindClass(env, CLASS_NATIVE_PATH);  //获取Java
    m_clazz = (jclass)(*env)->NewGlobalRef(env,jclassRef);
    resp_callback_mid =(*env)->GetStaticMethodID(
            env,m_clazz, str_resp_callback,
            "(ILjava/lang/String;Ljava/lang/String;)V");
    event_callback_mid =(*env)->GetStaticMethodID(
            env, m_clazz, str_event_callback_method,
            "(Ljava/lang/String;Ljava/lang/String;)V");
    rval  = cdt_cli_start();
    LOGD("cdt_cli_start %d", rval);


}



JNIEXPORT void JNICALL
Java_com_horzon_conduit_mynative_conduit_stop
(JNIEnv *env, jobject instance)
{
    LOGD("%s i = %d", __FUNCTION__,__LINE__);
    cdt_cli_stop();
    LOGD("%s i = %d", __FUNCTION__,__LINE__);
    //(*env)->DeleteLocalRef(env,resp_callback_mid);
    LOGD("%s i = %d", __FUNCTION__,__LINE__);
    //(*env)->DeleteLocalRef(env,m_stream_push_buffer_method_id);
    //LOGD("%s i = %d", __FUNCTION__,__LINE__);
    //(*env)->DeleteLocalRef(env,event_callback_mid);
    //LOGD("%s i = %d", __FUNCTION__,__LINE__);

}


static void
_event_callback(const char* type, const char* str)
{
    JNIEnv *env;
    (*g_jvm)->AttachCurrentThread(g_jvm,&env, NULL);
    jstring str_type = (*env)->NewStringUTF(env, type);
    jstring str_content = (*env)->NewStringUTF(env, str);
    (*env)->CallStaticVoidMethod(env,m_clazz, event_callback_mid,
            str_type, str_content);
    (*env)->DeleteLocalRef(env, str_type);
    (*env)->DeleteLocalRef(env, str_content);
    // (*g_jvm)->DetachCurrentThread(g_jvm);
}


JNIEXPORT void JNICALL
Java_com_horzon_conduit_mynative_conduit_async_1call
(JNIEnv *env, jobject instance, jstring module_,
 jstring method_, jstring content_) {

    const char *module = (*env)->GetStringUTFChars(env, module_, 0);
    const char *method = (*env)->GetStringUTFChars(env, method_, 0);
    const char *content = (*env)->GetStringUTFChars(env, content_, 0);


    int len = strlen(module) + strlen(method) + strlen(content) + 5;

    char *auxiliary = (char*)malloc(len);
    memset(auxiliary, 0, len);

    sprintf(auxiliary, "%s$$%s$$%s", module, method, content);

    response_handler_t handler;
    handler.auxiliary = auxiliary;
    handler.callback = _response_callback;
    LOGD("%s %d %s %s %s -- \n",__FUNCTION__,__LINE__, module, method, content);
    cdt_cli_request(handler, module, method, content);
    //cdt_cli_request(handler, "module1", "m1", "test");
    LOGD("%s %d -- \n",__FUNCTION__,__LINE__);
    (*env)->ReleaseStringUTFChars(env, module_, module);
    (*env)->ReleaseStringUTFChars(env, method_, method);
    (*env)->ReleaseStringUTFChars(env, content_, content);
    LOGD("%s %d\n",__FUNCTION__,__LINE__);

}


JNIEXPORT void JNICALL
Java_com_horzon_conduit_mynative_conduit_send_1event
(JNIEnv *env, jobject instance, jstring event_, jstring content_) {

    const char *event= (*env)->GetStringUTFChars(env, event_, 0);
    const char *content = (*env)->GetStringUTFChars(env, content_, 0);

    LOGD("%s %d %s  %s\n",__FUNCTION__,__LINE__, event,  content);

    cdt_cli_send_event(event, content);

    LOGD("%s %d\n",__FUNCTION__,__LINE__);
    (*env)->ReleaseStringUTFChars(env, event_, event);
    (*env)->ReleaseStringUTFChars(env, content_, content);
    LOGD("%s %d\n",__FUNCTION__,__LINE__);
}



JNIEXPORT void JNICALL
Java_com_horzon_conduit_mynative_conduit_client_1register_1events
(JNIEnv *env, jobject instance, jobjectArray oa) {
    int i = 0;
    jsize size = (*env)->GetArrayLength(env,oa);

    size = size > MAX_EVENTS_NUM? MAX_EVENTS_NUM:size;

    for (; i < size ;i++) {
        jstring obj = (jstring)(*env)->GetObjectArrayElement(env,oa,i);
        char *tmp = (char*)(*env)->GetStringUTFChars(env,obj,NULL);//得到字符串
        LOGD("%s %d tmp:%s\n", __FUNCTION__, __LINE__,tmp);
        if (tmp != NULL) {
            int len = strlen(tmp);
            if(len >= MAX_EVENT_LEN)
            {
                LOGE("event %s too long >= %d!\n",tmp,MAX_EVENT_LEN);
                continue;
            }else
            {
                memmove(_events[i], tmp,len);
            }

        }else
        {
            LOGE("MEET ERROR!\n");
        }
    }

    cdt_cli_register_events(_events, size, g_event_callback);
}
