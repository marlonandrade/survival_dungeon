//
//  Game.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "Game.h"

#include "Definitions.h"
#include "InitialRoom.h"

USING_NS_CC;

#pragma mark - Public Interface

void Game::setPlayerPosition(Vec2 position) {
  _playerPosition = position;
  
  this->getDungeon()->placeTilesAdjacentTo(position);
}

bool Game::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  this->_setupAvaiableRooms();
  this->_setupInitialPosition();
  
  return true;
}

#pragma mark - Private Interface

void Game::_setupInitialPosition() {
  auto dungeon = Dungeon::create();
  auto initialRoom = InitialRoom::create();
  dungeon->setRoomForPosition(initialRoom, INITIAL_POSITION);
  
  this->setDungeon(dungeon);
}

void Game::_setupAvaiableRooms() {
  
}

DungeonRoom* Game::_pickRandomRoom() {
  return this->getAvailableRooms().getRandomObject();
}
