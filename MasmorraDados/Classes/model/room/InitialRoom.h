//
//  InitialRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#ifndef __MasmorraDados__InitialRoom__
#define __MasmorraDados__InitialRoom__

#include "DungeonRoom.h"

class InitialRoom : public DungeonRoom {
public:
  CREATE_FUNC(InitialRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__MasmorraDados__InitialRoom__) */
