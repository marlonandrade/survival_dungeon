//
//  Events.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __SurvivalDungeon__Events__
#define __SurvivalDungeon__Events__

#define EVT_LEVEL_ADVANCED            "level_advanced"           // no data

#define EVT_TURN_HAS_ENDED            "turn_has_ended"           // data -> turn
#define EVT_TURN_HAS_STARTED          "turn_has_started"         // data -> turn

#define EVT_END_PLAYER_TURN           "end_player_turn"          // no data

#define EVT_DICE_STATE_NEW            "state_changed_new"        // data -> new state
#define EVT_DICE_STATE_OLD            "state_changed_old"        // data -> previous state

#define EVT_ACTION_DICE_DRAG_STARTED  "action_dice_drag_started" // data -> ActionDice
#define EVT_ACTION_DICE_DRAG_MOVED    "action_dice_drag_moved"   // data -> ActionDiceDragData
#define EVT_ACTION_DICE_DRAG_ENDED    "action_dice_drag_ended"   // data -> ActionDiceDragData
#define EVT_ACTION_DICES_ROLLED       "action_dices_rolled"      // data -> ActionDiceLayer

#define EVT_ACTION_FREE_BOOT_SPENT    "action_free_boot_spent"    // ?
#define EVT_ACTION_DICE_SPENT         "action_dice_spent"         // data -> ActionDice

#define EVT_CHARACTER_DIED            "character_died"            // no data

#define EVT_LAST_TILE_HAS_BEEN_PLACED "last_tile_has_been_placed" // data -> RoomPlacementData
#define EVT_ROOMS_HAVE_BEEN_PLACED    "rooms_have_been_placed"    // data -> RoomsPlacementsData

#define EVT_MONSTER_DICE_GENERATED    "monster_dice_generated"    // data -> MonsterRoomData

#define EVT_MONSTER_MOVED             "monter_moved"              // data -> MonsterMoveData
#define EVT_MONSTERS_FINISHED_MOVING  "monsters_finished_moving"  // no data
#define EVT_MONSTERS_FINISHED_RISING  "monsters_finished_rising"  // no data

#define EVT_MONSTER_KILLED            "monster_killed"            // data -> MonsterKilledData

#define EVT_DAMAGE_TAKEN              "damage_taken"              // data -> DamageTakenData
#define EVT_EXPERIENCE_CHANGED        "experience_changed"        // no data
#define EVT_COINS_CHANGED             "coins_changed"             // no data

#endif /* defined(__SurvivalDungeon__Events__) */
