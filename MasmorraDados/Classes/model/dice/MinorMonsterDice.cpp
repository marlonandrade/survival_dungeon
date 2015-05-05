//
//  MinorMonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MinorMonsterDice.h"

#include "Images.h"

#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MinorMonsterDice::init() {
  DiceFaces faces;
  
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_GOBLIN));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CULTISTA));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ESQUELETO));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ORC));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_ARANHA));
  faces.pushBack(DiceFace::createWithImagePath(IMG_DICE_MONSTER_MINOR_CARNICAL));
  
  if (!MonsterDice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MINOR_BLUR);
  
  return true;
}
