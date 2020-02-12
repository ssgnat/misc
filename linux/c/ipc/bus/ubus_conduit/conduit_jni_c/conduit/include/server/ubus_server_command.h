#ifndef UBUS_SERVER_COMMAND_H
#define UBUS_SERVER_COMMAND_H

#define UBUSD_SOCKET_PATH "/tmp/hzbus.sock"

const char *UBUS_AUDIO_NAME="hzbus_audio";



// ubus -s /tmp/ubusd call hzmedia stream '{"data":{\"command\":\"acquirestream\",\"state\":1,\"devid\":0,\"socketpath\":\"/tmp/video/client/1\"}}'
// {"data":"{\"command\":\"acquirestream\",\"state\":1,\"devid\":0,\"socketpath\":\"/tmp/video/client/1\"}"}

//hzubus -s /tmp/hzubusd.sock call hzaudio call '{"data":{"command":"synccall","detail":"test"}}'

// hzbus -s /tmp/hzbusd.sock call hzaudio stream '{"data":"{\"command\":\"synccall\",\"detail\":\"<passthrough to server>\"}"}'

//tags
const char *MODULE_TAG="command";

const char *SUB_MODULE_TAG_ACQUIRESTREAM="acquirestream"; //state:1|0, socket:unix socket name
const char *SUB_MODULE_TAG_STATE="state"; // 1:ok else nok
const char *SUB_MODULE_TAG_DEVID="devid"; //device number integer
const char *SUB_MODULE_TAG_UNIXNAME="socketpath";

const char *MAIN_MODULE_TAG_VIDEO="hzbus_video";
const char *MAIN_MODULE_TAG_AUDIO="hzbus_audio";
const char *MAIN_MODULE_TAG_NORMAL="normal";


//
#define HZVIDEO_OBJECT_NAME "hzvideo"
#define HZVIDEO_METHOD_STREAM "stream"
#define HZVIDEO_METHOD_STREAM_ARG1 "data"
#define HZVIDEO_METHOD_STREAM_ARG2 "rc"

#define HZAUDIO_OBJECT_NAME "hzaudio"
#define HZAUDIO_METHOD_STREAM "stream"
#define HZAUDIO_METHOD_STREAM_ARG1 "data"
#define HZAUDIO_METHOD_STREAM_ARG2 "rc"

//
#define HZSYSTEM_OBJECT_NAME "hzsystem"
#define HZSYSTEM_METHOD_CALL "call"
#define HZSYSTEM_METHOD_ARG1 "data"
#define HZSYSTEM_METHOD_ARG2 "rc"

#define HZCUSTOM_METHOD_ARG1 "data"


const char *SUB_MODULE_TAG_NORMAL_SYNC="synccall"; //normal sync command
const char *SUB_MODULE_TAG_DETAIL="detail"; //normal sync command

#endif