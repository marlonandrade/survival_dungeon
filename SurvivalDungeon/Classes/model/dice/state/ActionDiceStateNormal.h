//
//  ActionDiceStateNormal.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __SurvivalDungeon__ActionDiceStateNormal__
#define __SurvivalDungeon__ActionDiceStateNormal__

#include "DiceState.h"
#include "cocos2d.h"

class ActionDiceStateNormal : public DiceState {
public:
  CREATE_FUNC(ActionDiceStateNormal);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(Dice *dice);
};

#endif /* defined(__SurvivalDungeon__ActionDiceStateNormal__) */
