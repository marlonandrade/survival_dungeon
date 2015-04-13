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

class DungeonRoom : public GameObject {
public:
  CC_SYNTHESIZE(int, _distanceToPlayer, DistanceToPlayer);
  virtual std::string getImagePath() = 0;
  virtual bool isExplorable() = 0;
};

#endif /* defined(__MasmorraDados__DungeonRoom__) */
