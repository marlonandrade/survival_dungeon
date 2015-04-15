//
//  ActionDiceStateNormal.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __MasmorraDados__ActionDiceStateNormal__
#define __MasmorraDados__ActionDiceStateNormal__

#include "DiceState.h"
#include "cocos2d.h"

class ActionDiceStateNormal : public DiceState {
public:
  CREATE_FUNC(ActionDiceStateNormal);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(Dice *dice);
};

#endif /* defined(__MasmorraDados__ActionDiceStateNormal__) */
