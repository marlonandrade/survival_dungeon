LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
		   ../../Classes/animation/Shake.cpp \
		   ../../Classes/event_data/ActionDiceDragData.cpp \
		   ../../Classes/layer/ActionDiceLayer.cpp \
		   ../../Classes/layer/BackgroundLayer.cpp \
		   ../../Classes/layer/PlayerSkillsLayer.cpp \
		   ../../Classes/layer/ScrollableLayer.cpp \
		   ../../Classes/model/character/Character.cpp \
		   ../../Classes/model/dice/face/DiceFace.cpp \
		   ../../Classes/model/dice/ActionDice.cpp \
		   ../../Classes/model/dice/Dice.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateDisabled.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateNormal.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateRolled.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateSelected.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateSpent.cpp \
		   ../../Classes/model/room/DungeonRoom.cpp \
		   ../../Classes/model/room/InitialRoom.cpp \
		   ../../Classes/model/room/MinorMonsterRoom.cpp \
		   ../../Classes/model/room/RuneRoom.cpp \
		   ../../Classes/model/turn/DungeonTurn.cpp \
		   ../../Classes/model/turn/InitialTurn.cpp \
		   ../../Classes/model/turn/PlayerTurn.cpp \
		   ../../Classes/model/Dungeon.cpp \
		   ../../Classes/model/Game.cpp \
		   ../../Classes/model/GameObject.cpp \
		   ../../Classes/model/Monster.cpp \
		   ../../Classes/model/Player.cpp \
		   ../../Classes/model/RoomPlacement.cpp \
		   ../../Classes/model/Skill.cpp \
		   ../../Classes/scene/GameplayScene.cpp \
		   ../../Classes/scene/IntroScene.cpp \
		   ../../Classes/sprite/ActionDiceSprite.cpp \
		   ../../Classes/sprite/CharacterDiceSprite.cpp \
		   ../../Classes/sprite/DiceSprite.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Classes/animation \
		    $(LOCAL_PATH)/../../Classes/delegate \
		    $(LOCAL_PATH)/../../Classes/event_data \
		    $(LOCAL_PATH)/../../Classes/layer \
		    $(LOCAL_PATH)/../../Classes/model \
		    $(LOCAL_PATH)/../../Classes/model/character \
		    $(LOCAL_PATH)/../../Classes/model/dice \
		    $(LOCAL_PATH)/../../Classes/model/dice/face \
		    $(LOCAL_PATH)/../../Classes/model/dice/state \
		    $(LOCAL_PATH)/../../Classes/model/room \
		    $(LOCAL_PATH)/../../Classes/model/turn \
  		    $(LOCAL_PATH)/../../Classes/scene \
  		    $(LOCAL_PATH)/../../Classes/sprite

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
