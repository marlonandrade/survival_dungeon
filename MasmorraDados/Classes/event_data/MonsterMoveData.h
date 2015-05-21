//
//  MonsterMoveData.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/7/15.
//
//

#ifndef __MasmorraDados__MonsterMoveData__
#define __MasmorraDados__MonsterMoveData__

#include "GameObject.h"

#include "DungeonRoom.h"
#include "MonsterDice.h"

class MonsterMoveData : public GameObject {
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _origin, Origin);
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _destination, Destination);
  CC_SYNTHESIZE_RETAIN(MonsterDice*, _monsterDice, MonsterDice);
  
  CREATE_FUNC(MonsterMoveData);
};

#endif /* defined(__MasmorraDados__MonsterMoveData__) */

