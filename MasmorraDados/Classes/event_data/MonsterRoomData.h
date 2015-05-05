//
//  MonsterRoomData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/5/15.
//
//

#ifndef __MasmorraDados__MonsterRoomData__
#define __MasmorraDados__MonsterRoomData__

#include "GameObject.h"

#include "DungeonRoom.h"
#include "MonsterDice.h"

class MonsterRoomData : public GameObject {
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _room, Room);
  CC_SYNTHESIZE_RETAIN(MonsterDice*, _monsterDice, MonsterDice);
  CREATE_FUNC(MonsterRoomData);
};

#endif /* defined(__MasmorraDados__MonsterRoomData__) */
