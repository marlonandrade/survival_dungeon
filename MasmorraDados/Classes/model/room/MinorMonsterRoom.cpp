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

bool MinorMonsterRoom::init() {
  if (!DungeonRoom::init()) {
    return false;
  }
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto roomHasBeenPlacedCallback = CC_CALLBACK_1(MinorMonsterRoom::_handleRoomHasBeenPlaced, this);
  this->setRoomHasBeenPlacedListener(
    dispatcher->addCustomEventListener(EVT_ROOM_HAS_BEEN_PLACED, roomHasBeenPlacedCallback)
  );
  
  return true;
}

std::string MinorMonsterRoom::getImagePath() {
  return IMG_ROOM_MINOR_MONSTER;
}

bool MinorMonsterRoom::isExplorable() {
  return true;
}

#pragma mark - Private Interface

#pragma mark - Event Handlers

void MinorMonsterRoom::_handleRoomHasBeenPlaced(EventCustom* event) {
  auto placementData = (RoomPlacementData*) event->getUserData();
  
  if (placementData->getRoom() == this) {
    auto dice = MinorMonsterDice::create();
    this->addMonsterDice(dice);
    
    auto data = MonsterRoomData::create();
    data->setMonsterDice(dice);
    data->setRoom(this);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_MONSTER_DICE_GENERATED, data);
  }
}
