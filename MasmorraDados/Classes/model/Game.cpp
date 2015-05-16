//
//  Game.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "Game.h"

#include "Definitions.h"
#include "Events.h"
#include "Images.h"

#include "DownstairsRoom.h"
#include "MinorMonsterRoom.h"
#include "RuneRoom.h"
#include "TreasureRoom.h"

#include "DungeonTurn.h"
#include "InitialTurn.h"
#include "PlayerTurn.h"
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

void Game::setCharacterCoordinate(Vec2 coordinate) {
  _characterCoordinate = coordinate;
  
  this->getDungeon()->placeRoomsAdjacentTo(coordinate);
  this->getDungeon()->calculateRoomDistanceToPlayer(coordinate);
}

int Game::getLevel() {
  return _level;
}

void Game::setLevel(int level) {
  _level = level;
  
  this->setTurn(InitialTurn::create());
  this->_setupAvaiableRooms();
  this->_setupDungeon();
  this->_setupActionDices();
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
  
  this->setRoomPlacedDelegate(delegate);
  this->setLevel(1);
  
  this->_setupEventHandlers();
  
  return true;
}

void Game::setupCharacterInitialCoordinate() {
  this->setCharacterCoordinate(INITIAL_COORDINATE);
}

void Game::characterMovedTo(Vec2 coordinate) {
  this->setCharacterCoordinate(coordinate);
  this->_dispatchDiceSpent();
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

void Game::finishCurrentTurn() {
  _turn->finish(this);
}

void Game::restoreFreeBoot() {
  this->setFreeBootUsed(false);
}

#pragma mark - Private Interface

void Game::_setupDungeon() {
  auto dungeon = Dungeon::create();
  dungeon->setRoomPlacedDelegate(this->getRoomPlacedDelegate());
  dungeon->setNewRoomDataSource([&]() -> DungeonRoom* {
    return this->_pickRandomRoom();
  });
  dungeon->placeInitialRoom();
  
  this->setDungeon(dungeon);
}

void Game::_setupAvaiableRooms() {
  Vector<DungeonRoom*> rooms;
  
  int level = this->getLevel();
  
  int numberOfRunes = level * (level * RUNE_COEFICIENT) + RUNE_CONSTANT;
  for (int i = 0; i < numberOfRunes; i++) {
    rooms.pushBack(RuneRoom::create());
  }
  
  int numberOfMonsters = level * (level * MINOR_MONSTER_COEFICIENT) + MINOR_MONSTER_CONSTANT;
  for (int i = 0; i < numberOfMonsters; i++) {
    rooms.pushBack(MinorMonsterRoom::create());
  }
  
  int numberOfTreasures = level * (level * TREASURE_COEFICIENT) + TREASURE_CONSTANT;
  for (int i = 0; i < numberOfTreasures; i++) {
    rooms.pushBack(TreasureRoom::create());
  }
  
  rooms.pushBack(DownstairsRoom::create());
  
  
  this->_availableRooms = rooms;
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
  
  auto freeBootSpentCallback = CC_CALLBACK_1(Game::_handleActionFreeBootSpent, this);
  this->setFreeBootSpentListener(
    dispatcher->addCustomEventListener(EVT_ACTION_FREE_BOOT_SPENT, freeBootSpentCallback)
  );
  
  auto diceSpentCallback = CC_CALLBACK_1(Game::_handleActionDiceSpent, this);
  this->setDiceSpentListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICE_SPENT, diceSpentCallback)
  );
  
  auto endPlayerTurnCallback = CC_CALLBACK_1(Game::_handleEndPlayerTurn, this);
  this->setEndPlayerTurnListener(
    dispatcher->addCustomEventListener(EVT_END_PLAYER_TURN, endPlayerTurnCallback)
  );
}

DungeonRoom* Game::_pickRandomRoom() {
  auto randomRoom = this->_availableRooms.getRandomObject();
  
  if (randomRoom) {
    randomRoom->retain();
    this->_availableRooms.eraseObject(randomRoom);
  }
  
  return randomRoom;
}

void Game::_dispatchDiceSpent() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  if (!this->getFreeBootUsed()) {
    dispatcher->dispatchCustomEvent(EVT_ACTION_FREE_BOOT_SPENT);
  } else {
    auto dockedDices = this->getDockedDices();
    ActionDice* usedDice;
    for (auto dice : dockedDices) {
      if (dice->getSelectedFace()->getImagePath() == IMG_DICE_ACTION_BOOT && !dice->isSpent()) {
        usedDice = dice;
        break;
      }
    }
    
    dispatcher->dispatchCustomEvent(EVT_ACTION_DICE_SPENT, usedDice);
  }
}

#pragma mark - Event Handlers

void Game::_handleActionFreeBootSpent(EventCustom* event) {
  this->setFreeBootUsed(true);
}

void Game::_handleActionDiceSpent(EventCustom* event) {
  auto dice = (ActionDice*) event->getUserData();
  dice->setSpent();
}

void Game::_handleEndPlayerTurn(EventCustom* event) {
  if (this->isPlayerTurn()) {
    this->finishCurrentTurn();
  }
}
