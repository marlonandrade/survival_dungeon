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

#include "DungeonRoomType.h"

class DungeonRoom : public GameObject {
  CC_SYNTHESIZE(DungeonRoomType*, _type, Type);
  // TODO: implementar cost -> Vector de Action
  // CC_SYNTHESIZE(cocos2d::Vector<int>, _cost, Cost);
  
public:
  CREATE_FUNC(DungeonRoom);
};

#endif /* defined(__MasmorraDados__DungeonRoom__) */
