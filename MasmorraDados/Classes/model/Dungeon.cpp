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
  
  this->setTopMostRoomPosition(INITIAL_POSITION);
  this->setRightMostRoomPosition(INITIAL_POSITION);
  this->setBottomMostRoomPosition(INITIAL_POSITION);
  this->setLeftMostRoomPosition(INITIAL_POSITION);
  
  return true;
}

void Dungeon::setRoomForPosition(DungeonRoom* room, Vec2 position) {
  auto index = this->indexForPosition(position);
  
  if (position.y > this->getTopMostRoomPosition().y) {
    this->setTopMostRoomPosition(position);
  }
  
  if (position.x > this->getRightMostRoomPosition().x) {
    this->setRightMostRoomPosition(position);
  }
  
  if (position.y < this->getBottomMostRoomPosition().y) {
    this->setBottomMostRoomPosition(position);
  }
  
  if (position.x < this->getLeftMostRoomPosition().x) {
    this->setLeftMostRoomPosition(position);
  }
  
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

void Dungeon::calculateRoomDistanceToPlayer(Vec2 playerPosition) {
  for (auto room : this->_rooms) {
    auto index = std::get<0>(room);
    auto dungeonRoom = std::get<1>(room);
    
    auto position = this->positionForIndex(index);
    auto distance = abs(position.x - playerPosition.x) +
                    abs(position.y - playerPosition.y);
    
    dungeonRoom->setDistanceToPLayer(distance);
  }
}

std::vector<Vec2> Dungeon::adjacentPositionsTo(Vec2 position) {
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

std::string Dungeon::nameForPosition(Vec2 position) {
  std::stringstream ss;
  ss << this->indexForPosition(position);
  return ss.str();
}

int Dungeon::indexForPosition(Vec2 position) {
  return position.x * DUNGEON_SIZE + position.y;
}

Vec2 Dungeon::positionForIndex(int index) {
  auto x = index / DUNGEON_SIZE;
  auto y = index % DUNGEON_SIZE;
  return Vec2(x, y);
}

void Dungeon::setTopMostRoomPosition(Vec2 position) {
  _topMostRoomPosition = position;
}

Vec2 Dungeon::getTopMostRoomPosition() {
  return _topMostRoomPosition;
}

void Dungeon::setRightMostRoomPosition(Vec2 position) {
  _rightMostRoomPosition = position;
}

Vec2 Dungeon::getRightMostRoomPosition() {
  return _rightMostRoomPosition;
}

void Dungeon::setBottomMostRoomPosition(Vec2 position) {
  _bottomMostRoomPosition = position;
}

Vec2 Dungeon::getBottomMostRoomPosition() {
  return _bottomMostRoomPosition;
}

void Dungeon::setLeftMostRoomPosition(Vec2 position) {
  _leftMostRoomPosition = position;
}

Vec2 Dungeon::getLeftMostRoomPosition() {
  return _leftMostRoomPosition;
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
