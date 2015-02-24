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

void Dungeon::placeTilesAdjacentTo(Vec2 position) {
  auto top = Vec2(position.x, position.y - 1);
  auto topTile = this->getRoomForPosition(top);
  if (!topTile) {
    log("pick top tile");
    // pick a tile
  }
  
  auto right = Vec2(position.x + 1, position.y);
  auto rightTile = this->getRoomForPosition(right);
  if (!rightTile) {
    log("pick right tile");
    // pick a tile
  }
  
  auto bottom = Vec2(position.x, position.y + 1);
  auto bottomTile = this->getRoomForPosition(bottom);
  if (!bottomTile) {
    log("pick bottom tile");
    // pick a tile
  }
  
  auto left = Vec2(position.x - 1, position.y);
  auto leftTile = this->getRoomForPosition(left);
  if (!leftTile) {
    log("pick left tile");
    // pick a tile
  }
}

#pragma mark - Private Interface

int Dungeon::indexForPosition(cocos2d::Vec2 position) {
  return position.x * DUNGEON_SIZE + position.y;
}