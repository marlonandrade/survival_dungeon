//
//  TurnDelegate.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __MasmorraDados__TurnDelegate__
#define __MasmorraDados__TurnDelegate__

#include "cocos2d.h"

class Turn;

class TurnDelegate {
public:
  virtual void turnHasStarted(Turn* turn) = 0;
  virtual void turnHasEnded(Turn* turn) = 0;
};

#endif /* defined(__MasmorraDados__TurnDelegate__) */
