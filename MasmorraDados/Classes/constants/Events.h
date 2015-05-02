//
//  Events.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__Events__
#define __MasmorraDados__Events__

#define EVT_TURN_HAS_ENDED           "turn_has_ended"           // data -> turn
#define EVT_TURN_HAS_STARTED         "turn_has_started"         // data -> turn

#define EVT_END_PLAYER_TURN          "end_player_turn"

#define EVT_DICE_STATE_NEW           "state_changed_new"        // data -> new state
#define EVT_DICE_STATE_OLD           "state_changed_old"        // data -> previous state

#define EVT_ACTION_DICE_DRAG_STARTED "action_dice_drag_started" // data -> ActionDice
#define EVT_ACTION_DICE_DRAG_MOVED   "action_dice_drag_moved"   // data -> ActionDiceDragData
#define EVT_ACTION_DICE_DRAG_ENDED   "action_dice_drag_ended"   // data -> ActionDiceDragData
#define EVT_ACTION_DICES_ROLLED      "action_dices_rolled"      // data -> ActionDiceLayer

#define EVT_ACTION_FREE_BOOT_SPENT   "action_free_boot_spent"    // ?
#define EVT_ACTION_DICE_SPENT        "action_dice_spent"         // data -> ActionDice

#endif /* defined(__MasmorraDados__Events__) */
