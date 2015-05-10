//
//  TreasureRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/9/15.
//
//

#ifndef __MasmorraDados__TreasureRoom__
#define __MasmorraDados__TreasureRoom__

#include "DungeonRoom.h"

class TreasureRoom : public DungeonRoom {
public:
  CREATE_FUNC(TreasureRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__MasmorraDados__TreasureRoom__) */
