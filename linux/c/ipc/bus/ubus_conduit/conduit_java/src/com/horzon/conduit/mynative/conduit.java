package com.horzon.conduit.mynative;

import android.util.Log;
import java.lang.String;

public class conduit
{
    public static final String TAG="NATIVE_CONDUIT";

    //实现这个接口
    public interface conduit_callback_interface
    {
        //调用normal_sync_call函数后，结果回来
        //reqdata:like  modulename$$methodname$$content, made up of arguments of
        //function conduit_async_call
        //rc    : conduit_async_call return status
        //str   : conduit_async_call , result conduit server send back
        boolean  async_callback(String reqdata, int rc, String str_result);
        //调用client_ubus_register_events关注的事件的回调。
        boolean  event_callback(String type, String content);
    }

    public static int HZ_STREAM_TYPE_VIDEIO = 0;
    public static int HZ_STREAM_TYPE_AUDIO = 1;
    public static int HZ_STREAM_TYPE_UNKOWN = 2;
    //
    public static String  HZVIDEO_OBJECT_NAME= "hzmedia";
    public static String  HZVIDEO_METHOD_STREAM= "stream";
    public static String  HZVIDEO_METHOD_STREAM_ARG1= "data";
    public static String  HZVIDEO_METHOD_STREAM_ARG2= "rc";

    public static String  HZSYSTEM_OBJECT_NAME= "hzsystem";
    public static String  HZVIDEO_METHOD_OP= "op";
    public static String  HZSYSTEM_METHOD_ARG1= "data";
    public static String  HZSYSTEM_METHOD_ARG2= "rc";


    public static conduit_callback_interface conduit_callback;
 	public static String[] events;

 	static {
        System.loadLibrary("conduit_client_native_lib");
    }

    public static void start(conduit_callback_interface callback )
    {
        conduit_callback = callback;
        start();
    }

    /*
     * firstly call start_conduit, only once in the process life
     */
    public static native void start();
    public static native void stop();
    public static native void async_call(String module, String method,
            String content);
    public static native void async_call_timeout(String module, String method,
            String content, int timeout);
    public static native void send_event(String event,String content);
    public static native void register_events(String[] _events);

    public static void register_events_j(String[] _events)
    {
        events = _events;
        conduit.register_events(events);
    }

// callback
    public static void async_callback(int rc, String str, String resqdata)
    {
    	Log.d(TAG,"normal_callback  "+resqdata +"  rc:" + rc + " str:" + str);
        conduit_callback.async_callback(resqdata, rc, str);
    }

    public static void event_callback(String type, String content)
    {
        Log.d(TAG,"event_callback type:" + type + " content:" + content);
        conduit_callback.event_callback(type, content);
    }
}
