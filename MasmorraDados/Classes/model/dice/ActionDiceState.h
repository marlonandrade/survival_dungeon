//
//  ActionDiceState.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __MasmorraDados__ActionDiceState__
#define __MasmorraDados__ActionDiceState__

#include "cocos2d.h"

class ActionDiceSprite;

class ActionDiceState : public cocos2d::Ref {
public:
  virtual bool canChangeState() = 0;
  virtual void changeState(ActionDiceSprite* sprite) = 0;
};

#endif /* defined(__MasmorraDados__ActionDiceState__) */
