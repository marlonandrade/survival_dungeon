//
//  DiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#include "DiceSprite.h"

USING_NS_CC;

#pragma mark - Public Interface

DiceSprite* DiceSprite::createWithDice(Dice *dice) {
  auto diceSprite = new (std::nothrow) DiceSprite();
  if (diceSprite && diceSprite->initWithDice(dice)) {
    diceSprite->autorelease();
  } else {
    CC_SAFE_DELETE(diceSprite);
  }
  
  return diceSprite;
}

bool DiceSprite::initWithDice(Dice *dice) {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setDice(dice);
  
  return this;
}