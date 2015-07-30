LOCAL_PATH := $(call my-dir)

## prebuilt the static libs
include $(CLEAR_VARS)

LOCAL_MODULE := sift
LOCAL_SRC_FILES := libezsift.a

include $(PREBUILT_STATIC_LIBRARY)


## to call the static libs
include $(CLEAR_VARS)

LOCAL_MODULE    := test
LOCAL_SRC_FILES := test.cpp

LOCAL_STATIC_LIBRARIES += sift
LOCAL_LDLIBS +=  -llog -ldl

include $(BUILD_SHARED_LIBRARY)