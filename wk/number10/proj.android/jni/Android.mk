LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := game_shared

LOCAL_MODULE_FILENAME := libgame

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../Classes/*.c)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../android/custom/*.cpp)

LOCAL_SRC_FILES := hellocpp/main.cpp 
LOCAL_SRC_FILES += $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes                   
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/common
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../android/custom
                  

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static cocosdenshion_static cocos_extension_static
            
include $(BUILD_SHARED_LIBRARY)

$(call import-module,CocosDenshion/android) \
$(call import-module,cocos2dx) \
$(call import-module,extensions)
