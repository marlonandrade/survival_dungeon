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

class RoomPlacementData;

class DungeonRoom : public GameObject {
  CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vector<MonsterDice*>, _monsters, Monsters);
  CC_SYNTHESIZE(int, _distanceToPlayer, DistanceToPlayer);
  CC_SYNTHESIZE(cocos2d::Vec2, _coordinate, Coordinate);
public:
  CREATE_FUNC(DungeonRoom);
  virtual bool init();
  
  virtual void addMonsterDice(MonsterDice* monster);
  virtual void removeMonsterDice(MonsterDice* monster);
  
  virtual std::string getImagePath();
  virtual bool isExplorable();
  
  bool isPlayerInRoom();
  bool isEmpty();
  bool isFull();
  
  bool isCloserToPlayerThen(DungeonRoom* other);
  
  virtual void hasBeenPlaced(RoomPlacementData* placement);
};


#endif /* defined(__MasmorraDados__DungeonRoom__) */
