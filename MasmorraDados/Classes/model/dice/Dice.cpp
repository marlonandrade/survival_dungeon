//
//  Dice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dice.h"

#include "ActionDiceSprite.h"
#include "Definitions.h"
#include "DiceFace.h"
#include "Shake.h"

USING_NS_CC;

#pragma mark - Properties

DiceFace* Dice::getSelectedFace() {
  return _selectedFace;
}

void Dice::setSelectedFace(DiceFace *selectedFace) {
  CC_SAFE_RETAIN(selectedFace);
  CC_SAFE_RELEASE(_selectedFace);
  _selectedFace = selectedFace;
  
  auto sprite = this->getSprite();
  sprite->setTexture(selectedFace->getImagePath());
  
  auto blurSprite = CallFunc::create([=]() {
    sprite->setTexture(selectedFace->getDice()->getBlurImagePath());
  });
  auto shake = Shake::create(0.3, Vec2(3, 3));
  auto finalSprite = CallFunc::create([=]() {
    sprite->setTexture(selectedFace->getImagePath());
  });
  
  sprite->runAction(Sequence::create(blurSprite, shake, finalSprite, NULL));
}

DiceFaces Dice::getFaces() {
  return _faces;
}

void Dice::setFaces(DiceFaces faces) {
  _faces = faces;
  
  for (auto face : faces) {
    face->setDice(this);
  }
}

DiceState* Dice::getState() {
  return _state;
}

void Dice::setState(DiceState *state) {
  if (_state != state) {
    CC_SAFE_RETAIN(state);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_DICE_STATE_OLD, _state);
    
    CC_SAFE_RELEASE(_state);
    _state = state;
    
    dispatcher->dispatchCustomEvent(EVT_DICE_STATE_NEW, _state);
  }
}

#pragma mark - Public Interface

Dice* Dice::createWithFaces(DiceFaces faces) {
  auto dice = new (std::nothrow) Dice();
  if (dice && dice->initWithFaces(faces)) {
    dice->autorelease();
  } else {
    CC_SAFE_DELETE(dice);
  }
  
  return dice;
}

bool Dice::initWithFaces(DiceFaces faces) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setFaces(faces);
  this->setSprite(ActionDiceSprite::createWithDice(this));
  this->roll();
  
  return true;
}

void Dice::roll() {
  this->setSelectedFace(this->getFaces().getRandomObject());
}

bool Dice::canChangeState() {
  return this->getState()->canChangeState();
}

void Dice::changeState() {
  this->getState()->changeState(this);
}

void Dice::resetState() {
}

bool Dice::isSelected() {
  return false;
}

bool Dice::isDisabled() {
  return false;
}

void Dice::setDisabled() {
}

void Dice::setRolled() {
}