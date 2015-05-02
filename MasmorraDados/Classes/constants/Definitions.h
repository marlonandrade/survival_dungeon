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
#define DOCK_MARGIN                 5
#define END_TURN_MARGIN             5

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

#pragma mark - Z Order

#define DUNGEON_ROOM_Z_ORDER 0
#define GAME_OBJECTS_Z_ORDER 1
#define OVERLAY_Z_ORDER      10
#define DRAG_Z_ORDER_DELTA   10

#pragma mark - Errors

#define NO_ERROR                       0
#define NO_REROLL_AVAILABLE            0x9000

#pragma mark - Helpers

#define IS(object, class) dynamic_cast<class*>(object) > 0

#endif /* defined(__MasmorraDados__Definitions__) */
