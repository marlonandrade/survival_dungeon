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
		   ../../Classes/event_data/DamageTakenData.cpp \
		   ../../Classes/event_data/MonsterMoveData.cpp \
		   ../../Classes/event_data/MonsterRoomData.cpp \
		   ../../Classes/event_data/RoomPlacementData.cpp \
		   ../../Classes/event_data/RoomsPlacementsData.cpp \
		   ../../Classes/layer/HudLayer.cpp \
		   ../../Classes/layer/TurnChangeLayer.cpp \
		   ../../Classes/layer/dungeon/BackgroundLayer.cpp \
		   ../../Classes/layer/dungeon/DungeonLayer.cpp \
		   ../../Classes/layer/dungeon/ScrollableDungeonLayer.cpp \
		   ../../Classes/layer/player_turn/DiceSelectLayer.cpp \
		   ../../Classes/layer/player_turn/GameplayLayer.cpp \
		   ../../Classes/layer/player_turn/MagicDiceEffectLayer.cpp \
		   ../../Classes/layer/player_turn/PlayerTurnLayer.cpp \
		   ../../Classes/model/Dungeon.cpp \
		   ../../Classes/model/Game.cpp \
		   ../../Classes/model/GameObject.cpp \
		   ../../Classes/model/Monster.cpp \
		   ../../Classes/model/Player.cpp \
		   ../../Classes/model/Skill.cpp \
		   ../../Classes/model/character/Character.cpp \
		   ../../Classes/model/dice/ActionDice.cpp \
		   ../../Classes/model/dice/Dice.cpp \
		   ../../Classes/model/dice/MonsterDice.cpp \
		   ../../Classes/model/dice/MinorMonsterDice.cpp \
		   ../../Classes/model/dice/MajorMonsterDice.cpp \
		   ../../Classes/model/dice/face/DiceFace.cpp \
		   ../../Classes/model/dice/face/MonsterDiceFace.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateDisabled.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateNormal.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateRolled.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateSelected.cpp \
		   ../../Classes/model/dice/state/ActionDiceStateSpent.cpp \
		   ../../Classes/model/room/DownstairsRoom.cpp \
		   ../../Classes/model/room/DungeonRoom.cpp \
		   ../../Classes/model/room/InitialRoom.cpp \
		   ../../Classes/model/room/MinorMonsterRoom.cpp \
		   ../../Classes/model/room/RuneRoom.cpp \
		   ../../Classes/model/room/TreasureRoom.cpp \
		   ../../Classes/model/turn/DungeonTurn.cpp \
		   ../../Classes/model/turn/InitialTurn.cpp \
		   ../../Classes/model/turn/PlayerTurn.cpp \
		   ../../Classes/scene/GameplayScene.cpp \
		   ../../Classes/scene/IntroScene.cpp \
		   ../../Classes/node/ActionDiceSprite.cpp \
		   ../../Classes/node/CharacterDiceSprite.cpp \
		   ../../Classes/node/DiceSprite.cpp \
		   ../../Classes/node/DockableContainer.cpp \
		   ../../Classes/node/DungeonRoomSprite.cpp \
		   ../../Classes/node/EndTurnButton.cpp \
		   ../../Classes/node/FreeBootSprite.cpp \
		   ../../Classes/util/CoordinateUtil.cpp \
		   ../../Classes/util/DiceUtil.cpp \
		   ../../Classes/util/FileUtil.cpp \
		   ../../Classes/util/HighlightUtil.cpp \
		   ../../Classes/util/NodeUtil.cpp \
		   ../../Classes/util/OverlayUtil.cpp \
		   ../../Classes/util/PositionUtil.cpp \
		   ../../Classes/util/drag_handler/CommonDiceDragHandler.cpp \
		   ../../Classes/util/drag_handler/DiceDragHandlerFactory.cpp \
		   ../../Classes/util/drag_handler/HealDiceDragHandler.cpp \
		   ../../Classes/util/drag_handler/MagicDiceDragHandler.cpp \
		   ../../Classes/util/drag_handler/ShieldDiceDragHandler.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
		    $(LOCAL_PATH)/../../Classes/animation \
		    $(LOCAL_PATH)/../../Classes/constants \
		    $(LOCAL_PATH)/../../Classes/delegate \
		    $(LOCAL_PATH)/../../Classes/event_data \
		    $(LOCAL_PATH)/../../Classes/layer \
		    $(LOCAL_PATH)/../../Classes/layer/dungeon \
		    $(LOCAL_PATH)/../../Classes/layer/player_turn \
		    $(LOCAL_PATH)/../../Classes/model \
		    $(LOCAL_PATH)/../../Classes/model/character \
		    $(LOCAL_PATH)/../../Classes/model/dice \
		    $(LOCAL_PATH)/../../Classes/model/dice/face \
		    $(LOCAL_PATH)/../../Classes/model/dice/state \
		    $(LOCAL_PATH)/../../Classes/model/room \
		    $(LOCAL_PATH)/../../Classes/model/turn \
  		    $(LOCAL_PATH)/../../Classes/node \
  		    $(LOCAL_PATH)/../../Classes/scene \
  		    $(LOCAL_PATH)/../../Classes/util \
  		    $(LOCAL_PATH)/../../Classes/util/drag_handler

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
