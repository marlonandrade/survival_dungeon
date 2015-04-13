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

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateSelected::init() {
  return true;
}

bool ActionDiceStateSelected::canChangeState() {
  return true;
}

void ActionDiceStateSelected::changeState(ActionDiceSprite* sprite) {
  sprite->removeAllChildren();
  
  sprite->setDiceState(ActionDiceStateNormal::create());
}