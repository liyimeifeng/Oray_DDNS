LOCAL_PATH := $(call my-dir)



## to call the static libs
include $(CLEAR_VARS)

LOCAL_LDLIBS := -llog -ldl

LOCAL_MODULE:= phddns
LOCAL_SRC_FILES :=  base64.c blowfish.c generate.c log.c main.c md5.c phglobal.c phruncall.c phsocket.c phupdate.c

#LOCAL_C_INCLUDES += $(LOCAL_PATH)/include

include $(BUILD_SHARED_LIBRARY)


