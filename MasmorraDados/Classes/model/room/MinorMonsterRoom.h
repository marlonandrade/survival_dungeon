//
//  MinorMonsterRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __MasmorraDados__MinorMonsterRoom__
#define __MasmorraDados__MinorMonsterRoom__

#include "DungeonRoom.h"

class MinorMonsterRoom : public DungeonRoom {
public:
  CREATE_FUNC(MinorMonsterRoom);
  
  virtual std::string getImagePath();
  virtual bool isExplorable();
};

#endif /* defined(__MasmorraDados__MinorMonsterRoom__) */
