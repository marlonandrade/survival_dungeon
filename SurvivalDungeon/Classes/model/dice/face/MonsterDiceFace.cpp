//
//  MonsterDiceFace.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/7/15.
//
//

#include "MonsterDiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

MonsterDiceFace* MonsterDiceFace::create(std::string imagePath,
                                         int attack,
                                         int defense,
                                         int experience) {
  auto face = new (std::nothrow) MonsterDiceFace();
  if (face && face->init(imagePath, attack, defense, experience)) {
    face->autorelease();
  } else {
    CC_SAFE_DELETE(face);
  }
  return face;
}

bool MonsterDiceFace::init(std::string imagePath,
                           int attack,
                           int defense,
                           int experience) {
  if (!DiceFace::init(imagePath)) {
    return false;
  }
  
  this->setAttack(attack);
  this->setDefense(defense);
  this->setExperience(experience);
  
  return true;
}
