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
  
  virtual void initialize();
  virtual std::string getImagePath();
  virtual bool isExplorable();
};

#endif /* defined(__MasmorraDados__InitialRoom__) */
