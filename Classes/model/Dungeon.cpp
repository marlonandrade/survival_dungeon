//
//  Dungeon.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dungeon.h"

#include "Definitions.h"
#include "Events.h"

#include "CoordinateUtil.h"

#include "Game.h"
#include "InitialRoom.h"
#include "MinorMonsterRoom.h"
#include "MonsterDice.h"
#include "MonsterMoveData.h"
#include "RoomsPlacementsData.h"

USING_NS_CC;

#pragma mark - Public Interface

bool Dungeon::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  auto initial = INITIAL_COORDINATE;
  _farthestCoordinates.top = initial;
  _farthestCoordinates.right = initial;
  _farthestCoordinates.bottom = initial;
  _farthestCoordinates.left = initial;
  
  return true;
}

void Dungeon::placeInitialRoom() {
  this->_placeRoomAtCoordinate(InitialRoom::create(), INITIAL_COORDINATE);
}

void Dungeon::moveMonsters() {
  log("move monsters");
  
  auto playerCoordinate = Game::getInstance()->getCharacterCoordinate();
  auto playerRoom = this->getRoomForCoordinate(playerCoordinate);
  this->_moveMonstersForAdjacentRooms(playerRoom);

  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTERS_FINISHED_MOVING);
}

void Dungeon::riseMonsters() {
  log("rise monsters");
  
  for (auto roomData : _rooms) {
    auto room = std::get<1>(roomData);
    
    if (IS(room, MinorMonsterRoom)) {
      auto monsterRoom = (MinorMonsterRoom*) room;
      
      if (monsterRoom->isEmpty()) {
        monsterRoom->riseMonster();
      }
    }
  }
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_MONSTERS_FINISHED_RISING);
}

void Dungeon::resetMonsterMovedState() {
  for (auto roomData : _rooms) {
    auto origin = std::get<1>(roomData);
    
    for (auto monster : origin->getMonsters()) {
      monster->setMovedThisTurn(false);
    }
  }
}

DungeonRoom* Dungeon::getRoomForCoordinate(Vec2 coordinate) {
  return _rooms.at(CoordinateUtil::indexForCoordinate(coordinate));
}

Vec2 Dungeon::getCoordinateForRoom(DungeonRoom *room) {
  Vec2 coordinate = Vec2::ZERO;
  
  auto indexes = _rooms.keys(room);
  if (indexes.size()) {
    auto index = indexes.at(0);
    coordinate = CoordinateUtil::coordinateForIndex(index);
  }
  
  return coordinate;
}

DungeonRoom* Dungeon::getInitialRoom() {
  return this->getRoomForCoordinate(INITIAL_COORDINATE);
}

FarthestCoordinates Dungeon::getFarthestCoordinates() {
  return _farthestCoordinates;
}

void Dungeon::removeDamageDealtToMonsters() {
  for (auto roomData : this->_rooms) {
    auto room = std::get<1>(roomData);
    
    for (auto monster : room->getMonsters()) {
      monster->resetLife();
    }
  }
}

void Dungeon::placeRoomsAdjacentTo(Vec2 coordinate) {
  Vector<RoomPlacementData*> placements;
  
  for (Vec2 adjacentCoordinate : CoordinateUtil::adjacentCoordinatesTo(coordinate)) {
    auto placement = this->_placeNewRoomAtCoordinate(adjacentCoordinate);
    
    if (placement) {
      placements.pushBack(placement);
    }
  }
  
  auto placementsData = RoomsPlacementsData::create();
  placementsData->setPlacements(placements);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->dispatchCustomEvent(EVT_ROOMS_HAVE_BEEN_PLACED, placementsData);
}

void Dungeon::calculateRoomDistanceToPlayer(Vec2 playerCoordinate) {
  this->_resetDistanceToPlayer();
  
  auto playerRoom = this->getRoomForCoordinate(playerCoordinate);
  playerRoom->setDistanceToPlayer(0);
  this->_fillDistanceForAdjacentRooms(playerRoom);
}

#pragma mark - Private Interface

void Dungeon::_adjustFarthestCoordinates(Vec2 newCoordinate) {
  if (newCoordinate.y > _farthestCoordinates.top.y) {
    _farthestCoordinates.top = newCoordinate;
  }
  
  if (newCoordinate.x > _farthestCoordinates.right.x) {
    _farthestCoordinates.right = newCoordinate;
  }
  
  if (newCoordinate.y < _farthestCoordinates.bottom.y) {
    _farthestCoordinates.bottom = newCoordinate;
  }
  
  if (newCoordinate.x < _farthestCoordinates.left.x) {
    _farthestCoordinates.left = newCoordinate;
  }
}

void Dungeon::_resetDistanceToPlayer() {
  for (auto roomData : this->_rooms) {
    auto room = std::get<1>(roomData);
    room->setDistanceToPlayer(NOT_CALCULATED_DISTANCE);
  }
}

/*
 * Função recursiva que calcula a distância entre o jogador e a sala.
 *
 * Pega todas as salas adjacentes a sala passada como parâmetro e adiciona
 * 1 na distância.
 *
 * O ponto de entrada é a sala onde o próprio jogador está.
 * O ponto de fim é quando não há mais salas adjacentes posicionadas.
 */
void Dungeon::_fillDistanceForAdjacentRooms(DungeonRoom *room) {
  Vector<DungeonRoom*> visitedRooms;
  
  auto coordinates = CoordinateUtil::adjacentCoordinatesTo(room->getCoordinate());
  for (auto coordinate : coordinates) {
    auto adjacentRoom = this->getRoomForCoordinate(coordinate);
    if (adjacentRoom != NULL && room->isCloserToPlayerThen(adjacentRoom)) {
      adjacentRoom->setDistanceToPlayer(room->getDistanceToPlayer() + 1);
      visitedRooms.pushBack(adjacentRoom);
    }
  }
  
  for (auto visitedRoom : visitedRooms) {
    this->_fillDistanceForAdjacentRooms(visitedRoom);
  }
}

void Dungeon::_moveMonstersForAdjacentRooms(DungeonRoom *room) {
  Vector<DungeonRoom*>visitedRooms;
  
  auto coordinates = CoordinateUtil::adjacentCoordinatesTo(room->getCoordinate());
  for (auto coordinate : coordinates) {
    auto adjacentRoom = this->getRoomForCoordinate(coordinate);
    
    if (adjacentRoom != NULL) {
      if (room->isCloserToPlayerThen(adjacentRoom)) {
        for (auto monster : adjacentRoom->getMonsters()) {
          if (!monster->getMovedThisTurn() && !room->isFull()) {
            adjacentRoom->removeMonsterDice(monster);
            room->addMonsterDice(monster);
            
            monster->setMovedThisTurn(true);
            
            auto data = MonsterMoveData::create();
            data->setOrigin(adjacentRoom);
            data->setDestination(room);
            data->setMonsterDice(monster);
            
            auto dispatcher = Director::getInstance()->getEventDispatcher();
            dispatcher->dispatchCustomEvent(EVT_MONSTER_MOVED, data);
          }
        }
        
        visitedRooms.pushBack(adjacentRoom);
      }
    }
  }
  
  for (auto visitedRoom : visitedRooms) {
    this->_moveMonstersForAdjacentRooms(visitedRoom);
  }
}

RoomPlacementData* Dungeon::_placeRoomAtCoordinate(DungeonRoom* room, Vec2 coordinate) {
  _rooms.insert(CoordinateUtil::indexForCoordinate(coordinate), room);
  this->_adjustFarthestCoordinates(coordinate);
      
  auto placement = RoomPlacementData::create();
  placement->setCoordinate(coordinate);
  placement->setRoom(room);
  
  room->hasBeenPlaced(placement);
  
  return placement;
}

RoomPlacementData* Dungeon::_placeNewRoomAtCoordinate(Vec2 coordinate) {
  RoomPlacementData* placement = nullptr;
  
  auto alreadyPlacedRoom = this->getRoomForCoordinate(coordinate);
  auto newRoomDataSource = this->getNewRoomDataSource();
  
  if (!alreadyPlacedRoom && newRoomDataSource) {
    DungeonRoom* room = newRoomDataSource();
    
    if (room) {
      placement = this->_placeRoomAtCoordinate(room, coordinate);
    }
  }
  
  return placement;
}
