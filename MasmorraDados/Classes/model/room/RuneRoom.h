//
//  RuneRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __MasmorraDados__RuneRoom__
#define __MasmorraDados__RuneRoom__

#include "DungeonRoom.h"

class RuneRoom : public DungeonRoom {
public:
  CREATE_FUNC(RuneRoom);
  
  virtual void initialize();
  virtual std::string getImagePath();
  virtual bool isExplorable();
};

#endif /* defined(__MasmorraDados__RuneRoom__) */
