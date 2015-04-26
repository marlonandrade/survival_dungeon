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
#include "ActionDiceStateRolled.h"
#include "ActionDiceStateSelected.h"
#include "Definitions.h"
#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDice::init() {
  DiceFaces faces;
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_BOOT));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_BOW));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_HEAL));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_MAGIC));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_SHIELD));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_ACTION_SWORD));
  
  if (!Dice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_ACTION_BLUR);
  this->setState(ActionDiceStateNormal::create());
  
  return true;
}

void ActionDice::roll() {
  Dice::roll();
  
  this->setState(ActionDiceStateNormal::create());
  this->getSprite()->removeAllChildren();
}

void ActionDice::resetState() {
  Dice::resetState();
  
  this->setState(ActionDiceStateNormal::create());
}

bool ActionDice::isSelected() {
  return IS(this->getState(), ActionDiceStateSelected);
}

bool ActionDice::isDisabled() {
  return IS(this->getState(), ActionDiceStateDisabled);
}

void ActionDice::setDisabled() {
  Dice::setDisabled();
  
  auto sprite = this->getSprite();
  
  auto disabledSprite = Sprite::create(IMG_DICE_ACTION_DISABLED);
  disabledSprite->setPosition(Vec2(sprite->getContentSize().width / 2,
                                   sprite->getContentSize().height / 2));
  sprite->addChild(disabledSprite);
  
  this->setState(ActionDiceStateDisabled::create());
}

void ActionDice::setRolled() {
  Dice::setRolled();
  
  this->getSprite()->removeAllChildren();
  
  this->setState(ActionDiceStateRolled::create());
}