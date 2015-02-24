LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
		   ../../Classes/scene/CreditsScene.cpp \
		   ../../Classes/scene/GameplayScene.cpp \
		   ../../Classes/scene/IntroScene.cpp \
		   ../../Classes/scene/MainMenuScene.cpp \
		   ../../Classes/scene/NewGameScene.cpp \
		   ../../Classes/scene/OptionsScene.cpp \
		   ../../Classes/scene/RulesScene.cpp \
		   ../../Classes/model/dice/builder/ActionDiceFaceBuilder.cpp \
		   ../../Classes/model/dice/builder/DiceFaceBuilder.cpp \
		   ../../Classes/model/dice/builder/MonsterDiceFaceBuilder.cpp \
		   ../../Classes/model/dice/face/ActionDiceFace.cpp \
		   ../../Classes/model/dice/face/DiceFace.cpp \
		   ../../Classes/model/dice/face/MonsterDiceFace.cpp \
		   ../../Classes/model/dice/roller/ActionDiceRoller.cpp \
		   ../../Classes/model/dice/roller/DiceRoller.cpp \
		   ../../Classes/model/dice/ActionDice.cpp \
		   ../../Classes/model/dice/Dice.cpp \
		   ../../Classes/model/dice/MajorMonsterDice.cpp \
		   ../../Classes/model/dice/MinorMonsterDice.cpp \
		   ../../Classes/model/room/DungeonRoom.cpp \
		   ../../Classes/model/Character.cpp \
		   ../../Classes/model/Dungeon.cpp \
		   ../../Classes/model/DungeonFloor.cpp \
		   ../../Classes/model/Game.cpp \
		   ../../Classes/model/GameObject.cpp \
		   ../../Classes/model/GameOptions.cpp \
		   ../../Classes/model/GameResources.cpp \
		   ../../Classes/model/Monster.cpp \
		   ../../Classes/model/Player.cpp \
		   ../../Classes/model/Skill.cpp \
		   ../../Classes/model/SoloGame.cpp \
		   ../../Classes/ui/layer/BackgroundLayer.cpp \
		   ../../Classes/ui/layer/BaseMenuLayer.cpp \
		   ../../Classes/ui/layer/ExitLayer.cpp \
		   ../../Classes/ui/layer/InnerMenuLayer.cpp \
		   ../../Classes/ui/BackLabel.cpp \
		   ../../Classes/ui/BackMenu.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Classes/layer \
		    $(LOCAL_PATH)/../../Classes/model \
		    $(LOCAL_PATH)/../../Classes/model/dice \
		    $(LOCAL_PATH)/../../Classes/model/dice/builder \
		    $(LOCAL_PATH)/../../Classes/model/dice/face \
		    $(LOCAL_PATH)/../../Classes/model/dice/roller \
		    $(LOCAL_PATH)/../../Classes/model/enum \
		    $(LOCAL_PATH)/../../Classes/model/room \
  		    $(LOCAL_PATH)/../../Classes/scene \
		    $(LOCAL_PATH)/../../Classes/ui \
		    $(LOCAL_PATH)/../../Classes/ui/layer \

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
