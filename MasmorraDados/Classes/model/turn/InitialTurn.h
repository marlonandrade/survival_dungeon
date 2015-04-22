//
//  InitialTurn.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/22/15.
//
//

#ifndef __MasmorraDados__InitialTurn__
#define __MasmorraDados__InitialTurn__

#include "Turn.h"

class InitialTurn : public Turn {
public:
  CREATE_FUNC(InitialTurn);
  
  virtual void execute(Game* game);
};

#endif /* defined(__MasmorraDados__InitialTurn__) */
