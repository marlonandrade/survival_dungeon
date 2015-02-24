//
//  Dungeon.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dungeon.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

bool Dungeon::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  return true;
}

void Dungeon::setRoomForPosition(DungeonRoom* room, cocos2d::Vec2 position) {
  auto index = this->indexForPosition(position);
  _rooms.insert(index, room);
}

DungeonRoom* Dungeon::getRoomForPosition(cocos2d::Vec2 position) {
  auto index = this->indexForPosition(position);
  return _rooms.at(index);
}

DungeonRoom* Dungeon::getInitialRoom() {
  return this->getRoomForPosition(INITIAL_POSITION);
}

#pragma mark - Private Interface

int Dungeon::indexForPosition(cocos2d::Vec2 position) {
  return position.x * DUNGEON_SIZE + position.y;
}