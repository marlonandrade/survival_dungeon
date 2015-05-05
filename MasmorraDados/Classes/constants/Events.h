//
//  Events.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__Events__
#define __MasmorraDados__Events__

#define EVT_TURN_HAS_ENDED            "turn_has_ended"           // data -> turn
#define EVT_TURN_HAS_STARTED          "turn_has_started"         // data -> turn

#define EVT_END_PLAYER_TURN           "end_player_turn"

#define EVT_DICE_STATE_NEW            "state_changed_new"        // data -> new state
#define EVT_DICE_STATE_OLD            "state_changed_old"        // data -> previous state

#define EVT_ACTION_DICE_DRAG_STARTED  "action_dice_drag_started" // data -> ActionDice
#define EVT_ACTION_DICE_DRAG_MOVED    "action_dice_drag_moved"   // data -> ActionDiceDragData
#define EVT_ACTION_DICE_DRAG_ENDED    "action_dice_drag_ended"   // data -> ActionDiceDragData
#define EVT_ACTION_DICES_ROLLED       "action_dices_rolled"      // data -> ActionDiceLayer

#define EVT_ACTION_FREE_BOOT_SPENT    "action_free_boot_spent"    // ?
#define EVT_ACTION_DICE_SPENT         "action_dice_spent"         // data -> ActionDice

#define EVT_LAST_TILE_HAS_BEEN_PLACED "last_tile_has_been_placed" // data -> RoomPlacementData
#define EVT_ROOM_HAS_BEEN_PLACED      "room_has_been_placed"      // data -> RoomPlacementData

#define EVT_MONSTER_DICE_GENERATED    "monster_dice_generated"    // data -> MonsterRoomData

#define EVT_MONSTER_ADDED_TO_ROOM     "monster_added_to_room"     // data -> MonsterRoomData
#define EVT_MONSTER_REMOVED_FROM_ROOM "monster_removed_from_room" // data -> MonsterRoomData

#endif /* defined(__MasmorraDados__Events__) */
