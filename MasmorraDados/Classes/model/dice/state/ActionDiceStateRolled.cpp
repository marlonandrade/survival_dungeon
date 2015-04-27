//
//  ActionDiceStateRolled.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/26/15.
//
//

#include "ActionDiceStateRolled.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateRolled::init() {
  return true;
}

bool ActionDiceStateRolled::canChangeState() {
  return false;
}

void ActionDiceStateRolled::changeState(Dice *dice) {
  log("rolled change state");
}