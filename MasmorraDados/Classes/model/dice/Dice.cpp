//
//  Dice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dice.h"

#include "ActionDiceSprite.h"
#include "DiceFace.h"

USING_NS_CC;

DiceFace* Dice::getSelectedFace() {
  return _selectedFace;
}

void Dice::setSelectedFace(DiceFace *selectedFace) {
  if (_selectedFace != selectedFace) {
    CC_SAFE_RETAIN(selectedFace);
    CC_SAFE_RELEASE(_selectedFace);
    _selectedFace = selectedFace;
    
    this->getSprite()->setTexture(selectedFace->getImagePath());
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
