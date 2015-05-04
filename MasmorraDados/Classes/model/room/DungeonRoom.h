//
//  DungeonRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__DungeonRoom__
#define __MasmorraDados__DungeonRoom__

#include "GameObject.h"
#include "MonsterDice.h"

class DungeonRoom : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<MonsterDice*>, _monsters, Monsters);
  CC_SYNTHESIZE(int, _distanceToPlayer, DistanceToPlayer);
public:
  CREATE_FUNC(DungeonRoom);
  virtual bool init();
  
  virtual std::string getImagePath();
  virtual bool isExplorable();
};

#endif /* defined(__MasmorraDados__DungeonRoom__) */
