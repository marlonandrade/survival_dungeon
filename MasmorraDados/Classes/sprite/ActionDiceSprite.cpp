//
//  ActionDiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#include "ActionDiceSprite.h"

#include "ActionDice.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setTexture(this->_getFileNameForDice(nullptr));
  
  return true;
}

#pragma mark - Private Interface

std::string ActionDiceSprite::_getFileNameForDice(ActionDice* dice) {
  return "images/dice/sword.png";
}