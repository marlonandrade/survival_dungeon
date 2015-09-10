//
//  MinorMonsterRoom.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "MinorMonsterRoom.h"

#include "Events.h"
#include "Images.h"

#include "MonsterDice.h"
#include "MonsterRoomData.h"
#include "RoomPlacementData.h"

USING_NS_CC;

#pragma mark - Public Interface

std::string MinorMonsterRoom::getImagePath() {
  return IMG_ROOM_MINOR_MONSTER;
}

void MinorMonsterRoom::riseMonster() {
  auto monsterDice = MinorMonsterDice::create();
  this->addMonsterDice(monsterDice);
  
  auto data = MonsterRoomData::create();
  data->setMonsterDice(monsterDice);
  data->setRoom(this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTER_DICE_GENERATED, data);
}

void MinorMonsterRoom::hasBeenPlaced(RoomPlacementData *placementData) {
  DungeonRoom::hasBeenPlaced(placementData);
  this->riseMonster();
}
