LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
		   ../../Classes/layer/BaseMenuLayer.cpp \
		   ../../Classes/layer/ExitLayer.cpp \
		   ../../Classes/layer/InnerMenuLayer.cpp \
		   ../../Classes/scene/CreditsScene.cpp \
		   ../../Classes/scene/GameplayScene.cpp \
		   ../../Classes/scene/GameOptionsScene.cpp \
		   ../../Classes/scene/IntroScene.cpp \
		   ../../Classes/scene/MainMenuScene.cpp \
		   ../../Classes/scene/OptionsScene.cpp \
		   ../../Classes/scene/RulesScene.cpp \
		   ../../Classes/model/Game.cpp \
		   ../../Classes/model/GameOptions.cpp \
		   ../../Classes/ui/BackLabel.cpp \
		   ../../Classes/ui/BackMenu.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Classes/layer \
		    $(LOCAL_PATH)/../../Classes/model \
  		    $(LOCAL_PATH)/../../Classes/scene \
		    $(LOCAL_PATH)/../../Classes/ui

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
