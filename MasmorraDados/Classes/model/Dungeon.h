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

#include "DungeonRoom.h"

class Dungeon : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<DungeonRoom*>, _rooms, Rooms);
  
public:
  CREATE_FUNC(Dungeon);
};

#endif /* defined(__MasmorraDados__Dungeon__) */
