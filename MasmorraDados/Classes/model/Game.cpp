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
#include "InitialTurn.h"
#include "MinorMonsterRoom.h"
#include "PlayerTurn.h"
#include "RuneRoom.h"
#include "Turn.h"

USING_NS_CC;

#pragma mark - Getter and Setter

void Game::setTurn(Turn* turn) {
  if (_turn != turn) {
    CC_SAFE_RETAIN(turn);
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_TURN_HAS_ENDED, _turn);
    
    CC_SAFE_RELEASE(_turn);
    _turn = turn;
    
    dispatcher->dispatchCustomEvent(EVT_TURN_HAS_STARTED, _turn);
  }
}

void Game::setCharacterPosition(Vec2 position) {
  _characterPosition = position;
  
  this->getDungeon()->placeRoomsAdjacentTo(position);
  this->getDungeon()->calculateRoomDistanceToPlayer(position);
}

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
  
  this->setTurn(InitialTurn::create());
  this->_setupAvaiableRooms();
  this->_setupDungeon(delegate);
  this->_setupActionDices();
  this->_setupEventHandlers();
  
  return true;
}

Vector<ActionDice*> Game::getDockedDices() {
  Vector<ActionDice*> dockedDices;
  
  for (auto dice : this->getActionDices()) {
    if (dice->isDocked()) {
      dockedDices.pushBack(dice);
    }
  }
  
  return dockedDices;
}

ValueMap Game::getAvailableSkills() {
  ValueMap availableSkills;
  
  for (auto dice : this->getDockedDices()) {
    if (!dice->isSpent()) {
      std::string path = dice->getSelectedFace()->getImagePath();
      int numberOfSkills = availableSkills[path].asInt() + 1;
      availableSkills[path] = Value(numberOfSkills);
    }
  }
  
  return availableSkills;
}

bool Game::isInitialTurn() {
  return IS(_turn, InitialTurn);
}

bool Game::isPlayerTurn() {
  return IS(_turn, PlayerTurn);
}

void Game::executeCurrentTurn() {
  _turn->execute(this);
}

void Game::restoreFreeBoot() {
  this->setFreeBootUsed(false);
}

#pragma mark - Private Interface

void Game::_setupDungeon(RoomPlacedDelegate delegate) {
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

void Game::_setupActionDices() {
  Vector<ActionDice*> dices;
  
  for (int i = 0; i < 6; i++) {
    dices.pushBack(ActionDice::create());
  }
  
  this->setActionDices(dices);
}

void Game::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addCustomEventListener(EVT_ACTION_FREE_BOOT_SPENT,
                                     CC_CALLBACK_1(Game::_handleActionFreeBootSpent, this));
  dispatcher->addCustomEventListener(EVT_ACTION_DICE_SPENT,
                                     CC_CALLBACK_1(Game::_handleActionDiceSpent, this));
}

DungeonRoom* Game::_pickRandomRoom() {
  auto availableRooms = this->getAvailableRooms();
  
  auto randomRoom = availableRooms.getRandomObject();
  if (randomRoom) {
    availableRooms.eraseObject(randomRoom);
  }
  
  return randomRoom;
}

#pragma mark - Event Handlers

void Game::_handleActionFreeBootSpent(EventCustom* event) {
  this->setFreeBootUsed(true);
}

void Game::_handleActionDiceSpent(EventCustom* event) {
  auto dice = (ActionDice*) event->getUserData();
  dice->setSpent();
}