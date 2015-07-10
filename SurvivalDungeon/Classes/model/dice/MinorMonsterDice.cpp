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
  
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_RAT,
                                         ATTACK_MONSTER_MINOR_RAT,
                                         DEFENSE_MONSTER_MINOR_RAT,
                                         EXPERIENCE_MONSTER_MINOR_RAT));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_FROG,
                                         ATTACK_MONSTER_MINOR_FROG,
                                         DEFENSE_MONSTER_MINOR_FROG,
                                         EXPERIENCE_MONSTER_MINOR_FROG));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_BEE,
                                         ATTACK_MONSTER_MINOR_BEE,
                                         DEFENSE_MONSTER_MINOR_BEE,
                                         EXPERIENCE_MONSTER_MINOR_BEE));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_SCORPION,
                                         ATTACK_MONSTER_MINOR_SCORPION,
                                         DEFENSE_MONSTER_MINOR_SCORPION,
                                         EXPERIENCE_MONSTER_MINOR_SCORPION));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_SPIDER,
                                         ATTACK_MONSTER_MINOR_SPIDER,
                                         DEFENSE_MONSTER_MINOR_SPIDER,
                                         EXPERIENCE_MONSTER_MINOR_SPIDER));
  faces.pushBack(MonsterDiceFace::create(IMG_DICE_MONSTER_MINOR_MAMMOTH,
                                         ATTACK_MONSTER_MINOR_MAMMOTH,
                                         DEFENSE_MONSTER_MINOR_MAMMOTH,
                                         EXPERIENCE_MONSTER_MINOR_MAMMOTH));
  
  if (!MonsterDice::initWithFaces(faces)) {
    return false;
  }
  
  this->setBlurImagePath(IMG_DICE_MONSTER_MINOR_BLUR);
  
  return true;
}
