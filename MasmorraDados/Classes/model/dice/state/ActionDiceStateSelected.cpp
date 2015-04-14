//
//  ActionDiceStateSelected.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#include "ActionDiceStateSelected.h"

#include "ActionDiceSprite.h"
#include "ActionDiceStateNormal.h"
#include "Dice.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateSelected::init() {
  return true;
}

bool ActionDiceStateSelected::canChangeState() {
  return true;
}

void ActionDiceStateSelected::changeState(Dice* dice) {
  auto sprite = dice->getSprite();
  sprite->removeAllChildren();
  
  dice->setState(ActionDiceStateNormal::create());
}