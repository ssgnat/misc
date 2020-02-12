package com.horzon.conduit.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.horzon.conduit.mynative.conduit;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends Activity
    implements  conduit.conduit_callback_interface {

    private TextView log;
    private TextView tvpackagesize;

    private EditText capstreamettype;
    private EditText capstreametdevid;
    private EditText eventstolisten;
    private EditText eventinput;
    private EditText eventmsg;
    private EditText callmodulename;
    private EditText callmethodname;
    private EditText callcontent;

    private Button startconduit;
    private Button stopconduit;
    private Button capstream;
    private Button startlistenevent;
    private Button sendevent;
    private Button call;


    private int type = 0;
    private int devid = 0;
    private String modulename = "hzdisk";
    private String methodname = "format";
    private String synccallcontent
        = "{\"data\":\"/dev/block/sde\"}";
//    hzbus -s /tmp/hzbusd.sock call hzaudio call '{"data":"{\"command\":\"synccall\",\"detail\":\"<passthrough to server>\"}"}'
    private String eventname= "event";
    private String eventcontent= "{'test_event':'test 001'}";

    private String defaulteventstolisten= "event";

    private static int call_times = 0;
    private static int call_back_times = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        g_instance = this;
        log = (TextView)findViewById(R.id.log);

        eventstolisten = (EditText)findViewById(R.id.eventstolisten);
        eventinput = (EditText)findViewById(R.id.eventinput);
        eventmsg = (EditText)findViewById(R.id.eventmsg);
        callmodulename = (EditText)findViewById(R.id.callmodulename);
        callmethodname = (EditText)findViewById(R.id.callmethodname);
        callcontent = (EditText)findViewById(R.id.callcontent);

        startconduit = (Button)findViewById(R.id.startconduit);
        stopconduit = (Button)findViewById(R.id.stopconduit);
        startlistenevent = (Button)findViewById(R.id.startlistenevent);
        sendevent = (Button)findViewById(R.id.sendevent);
        call = (Button)findViewById(R.id.call);



        startconduit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {


                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        conduit.start(MainActivity.this);
                    }
                }).start();

                startconduit.setEnabled(false);
            }
        });

        stopconduit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        conduit.stop();
                    }
                }).start();
            }
        });

        startlistenevent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        String s = eventstolisten.getText().toString();
                        if(s.isEmpty())
                            s=defaulteventstolisten;

                        Log.d("TSS","监听的事件："+ s);
                        String[] ls = s.split(";");
                        conduit.register_events_j(ls);
                    }
                }).start();

            }
        });


        sendevent.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if(!eventinput.getText().toString().isEmpty())
                        {
                            eventname = eventinput.getText().toString();
                        }

                        if(!eventmsg.getText().toString().isEmpty())
                        {
                            eventcontent = eventmsg.getText().toString();
                        }
                        Log.d("TSS-->","发送的事件："+eventname
                            +" 发送的事件内容:"+eventcontent
                            +" 在android系统中使用命令：hzbus -s /tmp/hzbusd.sock "
                            +"send “event” '{“data”:“x”}'"
                            +"测试，使用中把中文符号换成英文符号");

                        int i = 0;
                        while(true)
                        {
                            conduit.send_event(eventname, String.valueOf(i++));

                            call_times++;
                            Log.d("-->","times:"+call_times);
                            try {
                                Thread.sleep(10);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }

                        }
                    }
                }).start();
            }
        });


        call.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if(!callmodulename.getText().toString().isEmpty())
                        {
                            modulename = callmodulename.getText().toString();
                        }

                        if(!callmethodname.getText().toString().isEmpty())
                        {
                            methodname = callmethodname.getText().toString();
                        }

                        if(!callcontent.getText().toString().isEmpty())
                        {
                            synccallcontent = callcontent.getText().toString();
                        }
                        Log.d("call-->", "同步调用模块名:"
                            +modulename+"  方法名:"
                            +methodname+"  具体内容:"
                            +synccallcontent+" time:"
                            +System.currentTimeMillis());
                        while(true)
                        {
                            conduit.async_call(modulename, methodname,synccallcontent);
                            call_times++;
                            Log.d("-->","times:"+call_times);
                            try {
                                Thread.sleep(1);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }

                            break;
                        }
                    }
                }).start();
            }
        });

    }

    public static final int MSG_LOG = 0;
    public static final int SHOW_RECLEN = 1;
    public static int bytelen = 0;

    public class MyHandler extends Handler {

        @Override
        public void handleMessage(Message msg) {
            Log.e("TSS1", String.valueOf(msg.what));
            switch (msg.what)
            {

                case MSG_LOG:
                    log.setText((String)(msg.obj));
                    break;

                case SHOW_RECLEN:
                    bytelen+= Integer.valueOf((String)msg.obj);
                    tvpackagesize.setText(String.valueOf(bytelen));
                    break;
            }
            super.handleMessage(msg);
        }
    }
    public  MyHandler s_myhandler = new MyHandler();
    public static MainActivity g_instance = null;
    public static final void sendmsg(int msgwhat, String msgstr)
    {
        Message msg = new Message();
        msg.what =msgwhat;
        msg.obj = msgstr;
        Log.e("<--back", msgstr+" time:"+System.currentTimeMillis());
        Log.e("<--back","times:"+call_back_times++);
        g_instance.s_myhandler.sendMessage(msg);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
//        jniUtils.nativeCleanup();
    }

    @Override
    public boolean async_callback(String reqdata,  int rc, String str_result)
    {
        String tmpstr = new String();
        tmpstr += "reqdata:" + reqdata;
        tmpstr += "rc:"+rc;
        tmpstr += " str:"+str_result;
        MainActivity.sendmsg(MainActivity.MSG_LOG, tmpstr);
        return false;
    }

    @Override
    public boolean event_callback(String type, String content) {

        String tmpstr = new String();
        tmpstr += "eventtype:"+type;
        tmpstr += " content:"+content;

        Log.e("TSS-", tmpstr);
        MainActivity.sendmsg(MainActivity.MSG_LOG, tmpstr);
        MainActivity.sendmsg(MainActivity.SHOW_RECLEN,String.valueOf(1));
        return false;

    }
}
