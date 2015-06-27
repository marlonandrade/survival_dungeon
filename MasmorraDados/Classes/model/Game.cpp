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

#include "MonsterDiceFace.h"

#include "DamageTakenData.h"

#include "DungeonTurn.h"
#include "InitialTurn.h"
#include "PlayerTurn.h"
#include "Turn.h"

#include "DiceUtil.h"

USING_NS_CC;

static Game *_game = nullptr;

Game* Game::getInstance() {
  if (!_game) {
    _game = new (std::nothrow) Game();
    _game->init();
  }
  
  return _game;
}

bool Game::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setPlayer(Player::create());
  this->setTurn(InitialTurn::create());
  
  this->_setupInitialState();
  
  this->_setupActionDices();
  
  this->_setupEventHandlers();
  
  return true;
}

void Game::resetForPlayerTurn() {
  this->setFreeBootUsed(false);
  for (auto actionDice : this->getActionDices()) {
    actionDice->setDocked(false);
  }
}

void Game::advanceLevel() {
  this->setLevel(this->getLevel() + 1);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_LEVEL_ADVANCED);
  
  this->setCharacterCoordinate(INITIAL_COORDINATE);
}

bool Game::canCharacterMove() {
  bool canMove = false;
  
  if (this->isPlayerTurn()) {
    auto playerTurn = (PlayerTurn *) this->getTurn();

    auto availableSkills = this->getAvailableSkills();
    
    bool playerHasBoot = availableSkills[IMG_DICE_ACTION_BOOT].asInt() ||
        !this->getFreeBootUsed();
    
    canMove = playerTurn->isActionDicesRolled() && playerHasBoot;
  }
  
  return canMove;
}

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
  
  this->calculateDamageTaken();
  this->getDungeon()->placeRoomsAdjacentTo(coordinate);
  this->getDungeon()->calculateRoomDistanceToPlayer(coordinate);
}

int Game::getLevel() {
  return _level;
}

void Game::setLevel(int level) {
  _level = level;
  
  this->_setupAvaiableRooms();
  this->_setupDungeon();
}

int Game::getExperience() {
  return _experience;
}

void Game::setExperience(int experience) {
  _experience = experience;
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_EXPERIENCE_CHANGED);
}

int Game::getCoins() {
  return _coins;
}

void Game::setCoins(int coins) {
  _coins = coins;
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_COINS_CHANGED);
}

int Game::getDamageTaken() {
  return _damageTaken;
}

void Game::setDamageTaken(int damageTaken) {
  _damageTaken = damageTaken;
  
  auto data = DamageTakenData::create();
  data->setDamage(damageTaken);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_DAMAGE_TAKEN, data);
}

#pragma mark - Public Interface

void Game::start() {
  this->advanceLevel();
}

void Game::characterMovedTo(Vec2 coordinate) {
  this->setCharacterCoordinate(coordinate);
  this->_dispatchDiceSpent();
  
  auto room = this->getDungeon()->getRoomForCoordinate(coordinate);
  if (IS(room, DownstairsRoom)) {
    this->advanceLevel();
  }
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

void Game::calculateDamageTaken() {
  auto room = this->getRoomForCharacterCoordinate();
  int damage = 0;
  for (auto monster : room->getMonsters()) {
    auto face = (MonsterDiceFace*) monster->getSelectedFace();
    damage += face->getAttack();
  }
  
  if (this->isPlayerTurn()) {
    auto playerTurn = (PlayerTurn*) this->getTurn();
    damage -= playerTurn->getDamageProtected();
  }
  
  this->setDamageTaken(damage);
}

DungeonRoom* Game::getRoomForCharacterCoordinate() {
  return this->getDungeon()->getRoomForCoordinate(this->getCharacterCoordinate());
}

#pragma mark - Private Interface

void Game::_setupInitialState() {
  this->setLevel(0);
  this->setExperience(INITIAL_EXPERIENCE);
  this->setCoins(INITIAL_COINS);
}

void Game::_setupDungeon() {
  auto dungeon = Dungeon::create();
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
      if (DiceUtil::isBootDice(dice) && !dice->isSpent()) {
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
