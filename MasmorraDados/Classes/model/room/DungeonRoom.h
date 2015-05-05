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
#include "MinorMonsterDice.h"

class DungeonRoom : public GameObject {
  CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<MonsterDice*>, _monsters, Monsters);
  CC_SYNTHESIZE(int, _distanceToPlayer, DistanceToPlayer);
public:
  CREATE_FUNC(DungeonRoom);
  virtual bool init();
  
  virtual void addMonsterDice(MonsterDice* monster);
  virtual void removeMonsterDice(MonsterDice* monster);
  
  virtual std::string getImagePath();
  virtual bool isExplorable();
};

#endif /* defined(__MasmorraDados__DungeonRoom__) */
