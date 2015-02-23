//
//  DungeonFloor.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__DungeonFloor__
#define __MasmorraDados__DungeonFloor__

#include "GameObject.h"

#include "DungeonRoom.h"

class DungeonFloor : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<DungeonRoom*>, _rooms, Rooms);
  
public:
  CREATE_FUNC(DungeonFloor);
};

#endif /* defined(__MasmorraDados__DungeonFloor__) */
