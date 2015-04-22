//
//  DungeonTurn.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __MasmorraDados__DungeonTurn__
#define __MasmorraDados__DungeonTurn__

#include "Turn.h"

class DungeonTurn : public Turn {
public:
  CREATE_FUNC(DungeonTurn);
  
  virtual void execute(Game* game);
};

#endif /* defined(__MasmorraDados__DungeonTurn__) */
