//
//  ActionDiceStateDisabled.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#include "ActionDiceStateDisabled.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateDisabled::init() {
  return true;
}

bool ActionDiceStateDisabled::canChangeState() {
  return false;
}

void ActionDiceStateDisabled::changeState(Dice *dice ) {
}
