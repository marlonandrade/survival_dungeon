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

class MonsterMoveOriginData : public GameObject {
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _origin, Origin);
  CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<MonsterDice*>, _monsterDices, MonsterDices);
  
  CREATE_FUNC(MonsterMoveOriginData);
};

class MonsterMoveData : public GameObject {
  CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<MonsterMoveOriginData*>,
                            _origins, Origins);
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _destination, Destination);
  
  CREATE_FUNC(MonsterMoveData);
};

#endif /* defined(__MasmorraDados__MonsterMoveData__) */

