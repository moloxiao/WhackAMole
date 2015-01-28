LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				   hellocpp/PayProxy.cpp\
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp\
				  ../../Classes/GameScene.cpp \
				  ../../Classes/Chinese.cpp \
				  ../../Classes/FloatWord.cpp \
				  ../../Classes/GAMEDATA.cpp \
				  ../../Classes/GameLayer.cpp \
				  ../../Classes/GamePause.cpp \
				  ../../Classes/GameResultLayer.cpp \
				  ../../Classes/GameResultScene.cpp \
				  ../../Classes/GameState.cpp \
				  ../../Classes/MenuScene.cpp \
				  ../../Classes/MenuLayer.cpp \
				  ../../Classes/TopMenu.cpp\
				  ../../Classes/Audio.cpp\
				  ../../Classes/PayHandler.cpp\
				  ../../Classes/SignIn.cpp\
				  ../../Classes/About.cpp\
				  ../../Classes/CallAndroidMethod.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
