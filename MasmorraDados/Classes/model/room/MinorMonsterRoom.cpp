//
//  MinorMonsterRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "MinorMonsterRoom.h"

#include "Events.h"
#include "Images.h"

#include "MonsterDice.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MinorMonsterRoom::init() {
  if (!DungeonRoom::init()) {
    return false;
  }
  
  auto dice = MonsterDice::create();
  this->addMonsterDice(dice);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTER_DICE_GENERATED, dice);
  
  return true;
}

std::string MinorMonsterRoom::getImagePath() {
  return IMG_ROOM_MINOR_MONSTER;
}

bool MinorMonsterRoom::isExplorable() {
  return true;
}

