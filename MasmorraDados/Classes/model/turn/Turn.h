//
//  Turn.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __MasmorraDados__Turn__
#define __MasmorraDados__Turn__

#include "cocos2d.h"

class Game;

class Turn {
public:
  virtual bool init() { return true; }
  virtual void execute(Game* game) = 0;
};

#endif /* defined(__MasmorraDados__Turn__) */
