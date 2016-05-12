
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := libpython2.7.so
LOCAL_MODULE:= python
include $(PREBUILT_SHARED_LIBRARY)
