//
//  ActionDiceStateDisabled.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#ifndef __SurvivalDungeon__ActionDiceStateDisabled__
#define __SurvivalDungeon__ActionDiceStateDisabled__

#include "DiceState.h"
#include "cocos2d.h"

class ActionDiceStateDisabled : public DiceState {
public:
  CREATE_FUNC(ActionDiceStateDisabled);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(Dice *dice);
};

#endif /* defined(__SurvivalDungeon__ActionDiceStateDisabled__) */
