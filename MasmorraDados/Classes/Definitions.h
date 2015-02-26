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

#define DUNGEON_SIZE     100
#define INITIAL_POSITION cocos2d::Vec2(DUNGEON_SIZE/2, DUNGEON_SIZE/2)
#define TILE_DIMENSION   100

#pragma mark - Game Mechanics

#define MAX_ACTION_REROLLS   2
#define CHARACTER_INITIAL_HP 6

#pragma mark - Animation Durations

#define PLACE_ROOM_DURATION       0.2
//#define PLACE_ROOM_DURATION       0.8
#define RETURN_CHARACTER_DURATION 0.2
#define BW_OVERLAY_DURATION       0.2

#pragma mark - Node Tags

#define OBJECTS_LAYER_TAG          1000
#define CONTROLS_LAYER_TAG         1001
#define BW_OVERLAY_LAYER_TAG       1002
#define CHARACTER_DICE_SPRITE_TAG  2000

#pragma mark - Z Order

#define DUNGEON_ROOM_Z_ORDER 0
#define GAME_OBJECTS_Z_ORDER 1
#define BW_OVERLAY_Z_ORDER   5

#pragma mark - Errors

#define NO_ERROR                       0
#define NO_REROLL_AVAILABLE            0x9000

#endif /* defined(__MasmorraDados__Definitions__) */
