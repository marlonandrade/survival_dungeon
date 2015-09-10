//
//  DiceState.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __SurvivalDungeon__DiceState__
#define __SurvivalDungeon__DiceState__

#include "GameObject.h"

class Dice;

class DiceState : public GameObject {
public:
  virtual bool canChangeState() = 0;
  virtual void changeState(Dice* dice) = 0;
};

#endif /* defined(__SurvivalDungeon__DiceState__) */
