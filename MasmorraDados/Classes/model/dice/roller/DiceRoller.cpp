//
//  DiceRoller.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 20/02/2015.
//
//

#include "DiceRoller.h"

#include "Dice.h"
#include "DiceFace.h"

USING_NS_CC;

DiceRoller* DiceRoller::createWithDices(const cocos2d::Vector<Dice *> dices) {
  auto diceRoller = new (std::nothrow) DiceRoller();
  if (diceRoller && diceRoller->initWithDices(dices)) {
    diceRoller->autorelease();
  } else {
    CC_SAFE_DELETE(diceRoller);
  }
  
  return diceRoller;
}

bool DiceRoller::initWithDices(const cocos2d::Vector<Dice *> dices) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setDices(dices);
  
  return true;
}

Vector<DiceFace*> DiceRoller::roll() {
  this->setRerolls(0);
  
  Vector<DiceFace*> faces;
  
  for (Dice* dice : this->getDices()) {
    faces.pushBack(dice->roll());
  }
  
  return faces;
}

Vector<DiceFace*> DiceRoller::reroll(cocos2d::Vector<DiceFace *> rolledFaces) {
  this->setRerolls(this->getRerolls() + 1);
  
  Vector<DiceFace*> faces;
  
  for(DiceFace* rolledFace : rolledFaces) {
    faces.pushBack(rolledFace->getDice()->roll());
  }
  
  return faces;
}