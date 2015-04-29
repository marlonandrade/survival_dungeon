//
//  ActionDiceStateSpent.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/28/15.
//
//

#ifndef __MasmorraDados__ActionDiceStateSpent__
#define __MasmorraDados__ActionDiceStateSpent__

#include "DiceState.h"
#include "cocos2d.h"

class ActionDiceStateSpent : public DiceState {
public:
  CREATE_FUNC(ActionDiceStateSpent);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(Dice *dice);
};

#endif /* defined(__MasmorraDados__ActionDiceStateSpent__) */
