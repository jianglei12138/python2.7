LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := boringssl/libcrypto.so
LOCAL_MODULE:= crypto
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := boringssl/libssl.so
LOCAL_MODULE:= ssl
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := interpreter

LOCAL_SRC_FILES := \
	main.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/ \
	$(LOCAL_PATH)/python2.7/

LOCAL_CFLAGS := -Xlinker --export-dynamic

LOCAL_LDLIBS := -llog -lz -lm
LOCAL_SHARED_LIBRARIES := python crypto ssl
include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/python/Android.mk