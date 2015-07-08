//
//  MinorMonsterDice.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#include "MinorMonsterDice.h"

#include "Images.h"
#include "Monsters.h"

#include "MonsterDiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MinorMonsterDice::init() {
  DiceFaces faces;
  
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_GOBLIN,
                                         ATTACK_MONSTER_MINOR_GOBLIN,
                                         DEFENSE_MONSTER_MINOR_GOBLIN,
                                         EXPERIENCE_MONSTER_MINOR_GOBLIN));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_CULTISTA,
                                         ATTACK_MONSTER_MINOR_CULTISTA,
                                         DEFENSE_MONSTER_MINOR_CULTISTA,
                                         EXPERIENCE_MONSTER_MINOR_CULTISTA));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_ESQUELETO,
                                         ATTACK_MONSTER_MINOR_ESQUELETO,
                                         DEFENSE_MONSTER_MINOR_ESQUELETO,
                                         EXPERIENCE_MONSTER_MINOR_ESQUELETO));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_ORC,
                                         ATTACK_MONSTER_MINOR_ORC,
                                         DEFENSE_MONSTER_MINOR_ORC,
                                         EXPERIENCE_MONSTER_MINOR_ORC));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_ARANHA,
                                         ATTACK_MONSTER_MINOR_ARANHA,
                                         DEFENSE_MONSTER_MINOR_ARANHA,
                                         EXPERIENCE_MONSTER_MINOR_ARANHA));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_CARNICAL,
                                         ATTACK_MONSTER_MINOR_CARNICAL,
                                         DEFENSE_MONSTER_MINOR_CARNICAL,
                                         EXPERIENCE_MONSTER_MINOR_CARNICAL));
  
  if (!MonsterDice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MINOR_BLUR);
  
  return true;
}
