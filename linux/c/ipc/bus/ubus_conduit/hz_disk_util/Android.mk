LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := hz_disk_util
LOCAL_MODULE_TAG := optional

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/../ \
    $(LOCAL_PATH)/../../ \

LOCAL_SRC_FILES := \
	hz_disk_util.c \
	../../ubus_conduit/conduit_server.c \
	../../ubus_conduit/conduit_client.c

LOCAL_FLAGS += -DANDROID

LOCAL_STATIC_LIBRARIES :=  liblog
LOCAL_SHARED_LIBRARIES +=  libandroid
LOCAL_SHARED_LIBRARIES +=  libhzparam
LOCAL_SHARED_LIBRARIES +=  libcjson
LOCAL_SHARED_LIBRARIES +=  libhisysmanagerservice
LOCAL_LDFLAGS += $(LOCAL_PATH)/../../bin/lib/libblobmsg_json.so
LOCAL_LDFLAGS += $(LOCAL_PATH)/../../bin/lib/libubox.so
LOCAL_LDFLAGS += $(LOCAL_PATH)/../../bin/lib/libhzbus.so

LOCAL_MODULE_CLASS := EXECUTABLES
include $(BUILD_EXECUTABLE)
