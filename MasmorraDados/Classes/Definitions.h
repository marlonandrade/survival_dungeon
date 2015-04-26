//
//  Definitions.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__Definitions__
#define __MasmorraDados__Definitions__

#define FONT_SCALE_RATIO 950

#pragma mark - Dimensions

#define DUNGEON_SIZE         100
#define INITIAL_POSITION     cocos2d::Vec2(DUNGEON_SIZE/2, DUNGEON_SIZE/2)
#define TILE_DIMENSION       100
#define TILE_PLACEMENT_SCALE 0.3

#define ACTION_DICE_BACKGROUND_BUTTON_MARGIN 5

#define ACTION_DICE_MARGIN          10
#define ACTION_DICE_MARGIN_PER_DICE 3

#pragma mark - Game Mechanics

#define MAX_ACTION_REROLLS   2
#define CHARACTER_INITIAL_HP 6

#pragma mark - Animation Durations

#define PLACE_ROOM_DURATION       0.5
#define RETURN_CHARACTER_DURATION 0.2
#define OVERLAY_DURATION          0.2
#define TURN_INFO_DURATION        1.5

#pragma mark - Colors / Alpha

#define OVERLAY_COLOR             cocos2d::Color4B(0, 0, 0, 0)
#define OVERLAY_OPACITY           150 // 255 -> fully opaque | 0 -> transparent

#pragma mark - Node Names

#define OBJECTS_LAYER_NAME         "ObjectsLayer"
#define CONTROLS_LAYER_NAME        "ControlsLayer"
#define OVERLAY_LAYER_NAME         "OverlayLayer"
#define SCROLLABLE_LAYER_NAME      "ScrollableLayer"
#define TURN_OVERLAY_LAYER_NAME    "TurnOverlayLayer"
#define CHARACTER_DICE_SPRITE_NAME "CharacterDiceSprite"
#define DICE_REROLL_BUTTON_NAME    "DiceRerollButton"
#define DICE_OK_BUTTON_NAME        "DiceOkButton"

#pragma mark - Z Order

#define DUNGEON_ROOM_Z_ORDER 0
#define GAME_OBJECTS_Z_ORDER 1
#define OVERLAY_Z_ORDER      10

#pragma mark - Errors

#define NO_ERROR                       0
#define NO_REROLL_AVAILABLE            0x9000

#pragma mark - Helpers

#define IS(object, class) dynamic_cast<class*>(object) > 0

#pragma mark - Image Paths

#define IMG_BACKGROUND             "background.png"
#define IMG_INTRO                  "intro.jpg"

#define IMG_BUTTON_OK_DISABLED     "button/ok/disabled.png"
#define IMG_BUTTON_OK_NORMAL       "button/ok/normal.png"
#define IMG_BUTTON_OK_SELECTED     "button/ok/selected.png"

#define IMG_BUTTON_REROLL_DISABLED "button/reroll/disabled_xx.png"
#define IMG_BUTTON_REROLL_NORMAL   "button/reroll/normal_xx.png"
#define IMG_BUTTON_REROLL_SELECTED "button/reroll/selected_xx.png"

#define IMG_DICE_ACTION_BLUR        "dice/action/blur.png"
#define IMG_DICE_ACTION_BOOT        "dice/action/boot.png"
#define IMG_DICE_ACTION_BOW         "dice/action/bow.png"
#define IMG_DICE_ACTION_DISABLED    "dice/action/disabled.png"
#define IMG_DICE_ACTION_HEAL        "dice/action/heal.png"
#define IMG_DICE_ACTION_MAGIC       "dice/action/magic.png"
#define IMG_DICE_ACTION_SELECTED    "dice/action/selected.png"
#define IMG_DICE_ACTION_SHIELD      "dice/action/shield.png"
#define IMG_DICE_ACTION_SWORD       "dice/action/sword.png"

#define IMG_DICE_CHAR               "dice/char/xx.png"

#define IMG_ROOM_INITIAL            "room/initial.png"
#define IMG_ROOM_MINOR_MONSTER      "room/minor_monster.png"
#define IMG_ROOM_RUNE               "room/rune.png"

#define IMG_TURN_DUNGEON            "turn/dungeon.png"
#define IMG_TURN_PLAYER             "turn/player.png"

#pragma mark - Events

#define EVT_TURN_HAS_ENDED          "turn_has_ended"        // data -> turn
#define EVT_TURN_HAS_STARTED        "turn_has_started"      // data -> turn

#define EVT_DICE_STATE_NEW          "state_changed_new"     // data -> new state
#define EVT_DICE_STATE_OLD          "state_changed_old"     // data -> previous state

#define EVT_ACTION_DICES_ROLLED     "action_dices_rolled"   // data -> ActionDiceLayer


#endif /* defined(__MasmorraDados__Definitions__) */
