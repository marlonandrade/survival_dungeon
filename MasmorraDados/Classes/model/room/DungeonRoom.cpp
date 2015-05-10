//
//  DungeonRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "DungeonRoom.h"

#include "Events.h"

#include "MonsterRoomData.h"
#include "RoomPlacementData.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DungeonRoom::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  return true;
}

void DungeonRoom::addMonsterDice(MonsterDice *monster) {
  _monsters.pushBack(monster);
  
  auto data = MonsterRoomData::create();
  data->setRoom(this);
  data->setMonsterDice(monster);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTER_ADDED_TO_ROOM, data);
}

void DungeonRoom::removeMonsterDice(MonsterDice *monster) {
  auto data = MonsterRoomData::create();
  data->setRoom(this);
  data->setMonsterDice(monster);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTER_REMOVED_FROM_ROOM, data);
  
  _monsters.eraseObject(monster);
}

std::string DungeonRoom::getImagePath() {
  return nullptr;
}

bool DungeonRoom::isExplorable() {
  return true;
}

bool DungeonRoom::isFull() {
  return _monsters.size() == 3;
}

bool DungeonRoom::isCloserToPlayerThen(DungeonRoom *other) {
  return this->getDistanceToPlayer() < other->getDistanceToPlayer();
}

void DungeonRoom::hasBeenPlaced(RoomPlacementData *placement) {
  this->setCoordinate(placement->getCoordinate());
}