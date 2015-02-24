//
//  Dungeon.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Dungeon__
#define __MasmorraDados__Dungeon__

#include "GameObject.h"

#include "Definitions.h"
#include "DungeonRoom.h"

typedef cocos2d::Map<int, DungeonRoom*> DungeonGrid;

class Dungeon : public GameObject {
private:
  DungeonGrid _rooms;
  
public:
  virtual bool init();
  CREATE_FUNC(Dungeon);
  
  void setRoomForPosition(DungeonRoom* room, cocos2d::Vec2 position);
  DungeonRoom* getRoomForPosition(cocos2d::Vec2 position);
  DungeonRoom* getInitialRoom();
  
  void placeTilesAdjacentTo(cocos2d::Vec2 position);
private:
  int indexForPosition(cocos2d::Vec2 position);
};

#endif /* defined(__MasmorraDados__Dungeon__) */
