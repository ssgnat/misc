#ifndef UBUS_SERVER_COMMAND_H
#define UBUS_SERVER_COMMAND_H

#define ubus_socket_path "/tmp/ubusd"

const char *UBUS_AUDIO_NAME="ubus_audio";



// ubus -s /tmp/ubusd call hzmedia stream '{"data":"{\"ubus_video\":{\"subname\":\"outstream\",\"state\":1,\"devid\":0,\"socketpath\":\"/tmp/video/client/1\"}}"}'
// {\"ubus_video\":{\"subname\":\"outstream\",\"state\":1,\"devid\":0,\"socketpath\":\"/tmp/video/client/1\"}}


//normal command:{\"normal\":{\"subname\":\"showvideo\",\"x\":1,\"y\":100,\"w\":199,\"h\":300}}

//tags
const char *SUB_MODULE_TAG="subname";

const char *SUB_MODULE_TAG_OUTSTREAM="outstream"; //state:1|0, socket:unix socket name
const char *SUB_MODULE_TAG_STATE="state"; // 1:ok else nok
const char *SUB_MODULE_TAG_DEVID="devid"; //device number integer
const char *SUB_MODULE_TAG_UNIXNAME="socketpath";

const char *MAIN_MODULE_TAG_VIDEO="ubus_video";
const char *MAIN_MODULE_TAG_AUDIO="ubus_audio";
const char *MAIN_MODULE_TAG_normal="normal";


//
#define HZVIDEO_OBJECT_NAME "hzmedia"
#define HZVIDEO_METHOD_STREAM "stream"
#define HZVIDEO_METHOD_STREAM_ARG1 "data"
#define HZVIDEO_METHOD_STREAM_ARG2 "rc"

#define HZSYSTEM_OBJECT_NAME "hzsystem"

const char *ubus_socket = "/tmp/ubusd";

const char *SUB_MODULE_TAG_NORMAL_SYNC="sync"; //normal sync command
const char *SUB_MODULE_TAG_DETAIL="detail"; //normal sync command

#endif