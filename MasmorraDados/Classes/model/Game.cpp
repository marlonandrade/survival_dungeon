//
//  Game.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "Game.h"

#include "Definitions.h"
#include "DungeonTurn.h"
#include "InitialRoom.h"
#include "MinorMonsterRoom.h"
#include "PlayerTurn.h"
#include "RuneRoom.h"

USING_NS_CC;

#pragma mark - Public Interface

Game* Game::createWithRoomPlacedDelegate(RoomPlacedDelegate delegate) {
  auto game = new (std::nothrow) Game();
  
  if (game && game->initWithRoomPlacedDelegate(delegate)) {
    game->autorelease();
  } else {
    CC_SAFE_DELETE(game);
  }
  
  return game;
}

bool Game::initWithRoomPlacedDelegate(RoomPlacedDelegate delegate) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setTurn(PlayerTurn::create());
  this->_setupAvaiableRooms();
  this->_setupInitialPosition(delegate);
  
  return true;
}

void Game::setTurn(Turn* turn) {
  _turn = turn;
}

void Game::setCharacterPosition(Vec2 position) {
  _characterPosition = position;
  
  this->getDungeon()->placeRoomsAdjacentTo(position);
}

#pragma mark - Private Interface

void Game::_setupInitialPosition(RoomPlacedDelegate delegate) {
  auto dungeon = Dungeon::create();
  dungeon->setRoomPlacedDelegate(delegate);
  dungeon->setNewRoomDataSource([&]() -> DungeonRoom* {
    return this->_pickRandomRoom();
  });
  
  auto initialRoom = InitialRoom::create();
  dungeon->setRoomForPosition(initialRoom, INITIAL_POSITION);
  
  this->setDungeon(dungeon);
}

void Game::_setupAvaiableRooms() {
  Vector<DungeonRoom*> rooms;
  
  for (int i = 0; i < 100; i++) {
    if (i % 10 > 2) {
      rooms.pushBack(RuneRoom::create());
    } else {
      rooms.pushBack(MinorMonsterRoom::create());
    }
  }
  
  this->setAvailableRooms(rooms);
}

DungeonRoom* Game::_pickRandomRoom() {
  auto availableRooms = this->getAvailableRooms();
  
  auto randomRoom = availableRooms.getRandomObject();
  if (randomRoom) {
    availableRooms.eraseObject(randomRoom);
  }
  
  return randomRoom;
}
