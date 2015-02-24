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

#pragma mark - Private Interface

bool Game::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setupInitialPosition();
  
  return true;
}

void Game::setupInitialPosition() {
  Vec2 playerPosition = INITIAL_POSITION;
  
  this->setPlayerPosition(playerPosition);
  
  auto dungeon = Dungeon::create();
  auto initialRoom = InitialRoom::create();
  dungeon->setRoomForPosition(initialRoom, playerPosition);
  
  this->setDungeon(dungeon);
}

DungeonRoom* Game::pickRandomRoom() {
  return this->getAvailableRooms().getRandomObject();
}