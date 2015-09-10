//
//  MajorMonsterDice.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MajorMonsterDice.h"

#include "Images.h"

#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MajorMonsterDice::init() {
  DiceFaces faces;
  
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_BEE));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_FROG));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_MAMMOTH));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_RAT));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_SCORPION));
  faces.pushBack(DiceFace::create(IMG_DICE_MONSTER_MAJOR_SPIDER));
  
  if (!MonsterDice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MAJOR_BLUR);
  
  return true;
}
