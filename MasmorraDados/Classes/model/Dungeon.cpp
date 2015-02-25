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

void Dungeon::setRoomForPosition(DungeonRoom* room, Vec2 position) {
  auto index = this->indexForPosition(position);
  _rooms.insert(index, room);
}

DungeonRoom* Dungeon::getRoomForPosition(Vec2 position) {
  auto index = this->indexForPosition(position);
  return _rooms.at(index);
}

DungeonRoom* Dungeon::getInitialRoom() {
  return this->getRoomForPosition(INITIAL_POSITION);
}

void Dungeon::placeRoomsAdjacentTo(Vec2 position) {
  Vector<RoomPlacement*> placements;
  
  auto top = Vec2(position.x, position.y + 1);
  placements.pushBack(this->_placeNewRoomAtPosition(top));
  
  auto right = Vec2(position.x + 1, position.y);
  placements.pushBack(this->_placeNewRoomAtPosition(right));
  
  auto bottom = Vec2(position.x, position.y - 1);
  placements.pushBack(this->_placeNewRoomAtPosition(bottom));
  
  auto left = Vec2(position.x - 1, position.y);
  placements.pushBack(this->_placeNewRoomAtPosition(left));
  
  auto roomPlacedDelegate = this->getRoomPlacedDelegate();
  if (roomPlacedDelegate) {
    roomPlacedDelegate(placements);
  }
}

#pragma mark - Private Interface

int Dungeon::indexForPosition(cocos2d::Vec2 position) {
  return position.x * DUNGEON_SIZE + position.y;
}

RoomPlacement* Dungeon::_placeNewRoomAtPosition(Vec2 position) {
  RoomPlacement* placement;
  
  auto alreadyPlacedRoom = this->getRoomForPosition(position);
  auto newRoomDataSource = this->getNewRoomDataSource();
  
  if (!alreadyPlacedRoom && newRoomDataSource) {
    DungeonRoom* room = newRoomDataSource();
    this->setRoomForPosition(room, position);
    
    placement = RoomPlacement::create();
    placement->setPosition(position);
    placement->setRoom(room);
  }
  
  return placement;
}
