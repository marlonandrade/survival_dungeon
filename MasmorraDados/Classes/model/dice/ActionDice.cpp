//
//  ActionDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDice.h"

#include "ActionDiceStateNormal.h"
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
  
  this->setState(ActionDiceStateNormal::create());
  
  return true;
}