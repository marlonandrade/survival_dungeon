//
//  ActionDiceStateSpent.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/28/15.
//
//

#include "ActionDiceStateSpent.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateSpent::init() {
  return true;
}

bool ActionDiceStateSpent::canChangeState() {
  return false;
}

void ActionDiceStateSpent::changeState(Dice *dice) {
}
