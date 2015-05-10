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
#include "MonsterRoomData.h"
#include "RoomPlacementData.h"

USING_NS_CC;

#pragma mark - Public Interface

std::string MinorMonsterRoom::getImagePath() {
  return IMG_ROOM_MINOR_MONSTER;
}

void MinorMonsterRoom::hasBeenPlaced(RoomPlacementData *placementData) {
  DungeonRoom::hasBeenPlaced(placementData);
  
  auto dice = MinorMonsterDice::create();
  this->addMonsterDice(dice);
  
  auto data = MonsterRoomData::create();
  data->setMonsterDice(dice);
  data->setRoom(this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTER_DICE_GENERATED, data);
}