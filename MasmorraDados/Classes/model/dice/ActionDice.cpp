//
//  ActionDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDice.h"

#include "ActionDiceStateDisabled.h"
#include "ActionDiceStateNormal.h"
#include "ActionDiceStateSelected.h"
#include "Definitions.h"
#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDice::init() {
  DiceFaces faces;
  faces.pushBack(DiceFace::createWithImagePath("images/dice/boot.png"));
  faces.pushBack(DiceFace::createWithImagePath("images/dice/bow.png"));
  faces.pushBack(DiceFace::createWithImagePath("images/dice/heal.png"));
  faces.pushBack(DiceFace::createWithImagePath("images/dice/magic.png"));
  faces.pushBack(DiceFace::createWithImagePath("images/dice/shield.png"));
  faces.pushBack(DiceFace::createWithImagePath("images/dice/sword.png"));
  
  if (!Dice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath("images/dice/blur.png");
  this->setState(ActionDiceStateNormal::create());
  
  return true;
}

void ActionDice::roll() {
  Dice::roll();
  
  this->setState(ActionDiceStateNormal::create());
  this->getSprite()->removeAllChildren();
}

bool ActionDice::isSelected() {
  return IS(this->getState(), ActionDiceStateSelected);
}

bool ActionDice::isDisabled() {
  return IS(this->getState(), ActionDiceStateDisabled);
}

void ActionDice::setDisabled() {
  auto sprite = this->getSprite();
  
  auto disabledSprite = Sprite::create("images/dice/disabled.png");
  disabledSprite->setPosition(Vec2(sprite->getContentSize().width / 2,
                                   sprite->getContentSize().height / 2));
  sprite->addChild(disabledSprite);
  
  this->setState(ActionDiceStateDisabled::create());
}