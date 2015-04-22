//
//  PlayerTurn.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __MasmorraDados__PlayerTurn__
#define __MasmorraDados__PlayerTurn__

#include "cocos2d.h"
#include "Turn.h"

class PlayerTurn : public Turn {
public:
  CREATE_FUNC(PlayerTurn);
  
  virtual void execute(Game* game);
};


#endif /* defined(__MasmorraDados__PlayerTurn__) */
