//
//  ActionDiceStateSelected.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __SurvivalDungeon__ActionDiceStateSelected__
#define __SurvivalDungeon__ActionDiceStateSelected__

#include "DiceState.h"
#include "cocos2d.h"

class ActionDiceStateSelected : public DiceState {
public:
  CREATE_FUNC(ActionDiceStateSelected);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(Dice* dice);
};

#endif /* defined(__SurvivalDungeon__ActionDiceStateSelected__) */
