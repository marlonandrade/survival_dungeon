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
  
  // armazenar top, left, bottom e right
  
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
  
  for (Vec2 adjacentPosition : this->adjacentPositionsTo(position)) {
    auto placement = this->_placeNewRoomAtPosition(adjacentPosition);
    
    if (placement) {
      placements.pushBack(placement);
    }
  }
  
  auto roomPlacedDelegate = this->getRoomPlacedDelegate();
  if (roomPlacedDelegate) {
    roomPlacedDelegate(placements);
  }
}

std::vector<Vec2> Dungeon::adjacentPositionsTo(cocos2d::Vec2 position) {
  std::vector<Vec2> adjacentPositions;
  
  auto top = Vec2(position.x, position.y + 1);
  adjacentPositions.push_back(top);
  
  auto right = Vec2(position.x + 1, position.y);
  adjacentPositions.push_back(right);
  
  auto bottom = Vec2(position.x, position.y - 1);
  adjacentPositions.push_back(bottom);
  
  auto left = Vec2(position.x - 1, position.y);
  adjacentPositions.push_back(left);
  
  return adjacentPositions;
}

std::string Dungeon::nameForPosition(cocos2d::Vec2 position) {
  return std::to_string(this->indexForPosition(position));
}

int Dungeon::indexForPosition(cocos2d::Vec2 position) {
  return position.x * DUNGEON_SIZE + position.y;
}

#pragma mark - Private Interface

RoomPlacement* Dungeon::_placeNewRoomAtPosition(Vec2 position) {
  RoomPlacement* placement = nullptr;
  
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
