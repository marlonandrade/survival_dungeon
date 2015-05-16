//
//  Dungeon.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dungeon.h"

#include "Definitions.h"
#include "Events.h"

#include "CoordinateUtil.h"
#include "MonsterMoveData.h"

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

void Dungeon::moveMonsters() {
  log("move monsters");
  
  Vector<MonsterMoveData*> movements;
  
  
  for (auto room : this->_rooms) {
    auto origin = std::get<1>(room);
    
    auto monsters = origin->getMonsters();
    if (monsters.size()) {
      auto coordinate = origin->getCoordinate();
      auto adjacentCoordinates = CoordinateUtil::adjacentCoordinatesTo(coordinate);
      
      DungeonRoom* destination = origin;
      for (auto adjacentCoordinate : adjacentCoordinates) {
        auto adjacent = this->getRoomForCoordinate(adjacentCoordinate);
        
        if (adjacent != NULL) {
          if (adjacent->isCloserToPlayerThen(destination) && !adjacent->isFull()) {
            destination = adjacent;
          }
        }
      }
      
      if (destination != NULL && destination != origin) {
        auto data = MonsterMoveData::create();
        data->setOrigin(origin);
        data->setDestination(destination);
        data->setMonsterDices(origin->getMonsters());
        movements.pushBack(data);
      }
    }
  }
  
  for (auto movement : movements) {
    for (auto monster : movement->getMonsterDices()) {
      movement->getOrigin()->removeMonsterDice(monster);
      movement->getDestination()->addMonsterDice(monster);
    }
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_MONSTER_MOVED, movement);
  }
  // MOVER MONSTROS
  // - primeiro monstros que dão mais xp
  // - movem em direção ao jogador mais proximo
}

void Dungeon::riseMonsters() {
  log("rise monsters");
  // NASCER MONSTROS
  // - somente nos andares que tiver jogador
  // - somente nos tiles de monstro vazios
  // - nasce primeiro nos mais perto dos player
}

void Dungeon::setRoomForCoordinate(DungeonRoom* room, Vec2 coordinate) {
  _rooms.insert(CoordinateUtil::indexForCoordinate(coordinate), room);
  this->_adjustFarthestCoordinates(coordinate);
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

void Dungeon::placeRoomsAdjacentTo(Vec2 coordinate) {
  Vector<RoomPlacementData*> placements;
  
  for (Vec2 adjacentCoordinate : CoordinateUtil::adjacentCoordinatesTo(coordinate)) {
    auto placement = this->_placeNewRoomAtCoordinate(adjacentCoordinate);
    
    if (placement) {
      placements.pushBack(placement);
    }
  }
  
  auto roomPlacedDelegate = this->getRoomPlacedDelegate();
  if (roomPlacedDelegate) {
    roomPlacedDelegate(placements);
    
    for (auto placement : placements) {
      auto room = placement->getRoom();
      room->hasBeenPlaced(placement);
    }
  }
}

void Dungeon::calculateRoomDistanceToPlayer(Vec2 playerCoordinate) {
  this->_resetDistanceToPlayer();
  
  auto playerRoom = this->getRoomForCoordinate(playerCoordinate);
  playerRoom->setDistanceToPlayer(0);
  this->_fillDistanceForAdjacentRooms(playerRoom);
}

FarthestCoordinates Dungeon::getFarthestCoordinates() {
  return _farthestCoordinates;
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
  for (auto room : this->_rooms) {
    auto dungeonRoom = std::get<1>(room);
    dungeonRoom->setDistanceToPlayer(NOT_CALCULATED_DISTANCE);
  }
}

void Dungeon::_fillDistanceForAdjacentRooms(DungeonRoom *room) {
  Vector<DungeonRoom*> visitedRooms;
  
  auto coordinates = CoordinateUtil::adjacentCoordinatesTo(room->getCoordinate());
  for (auto coordinate : coordinates) {
    auto adjacentRoom = this->getRoomForCoordinate(coordinate);
    if (adjacentRoom != NULL &&
        adjacentRoom->getDistanceToPlayer() > room->getDistanceToPlayer()) {
      adjacentRoom->setDistanceToPlayer(room->getDistanceToPlayer() + 1);
      
      visitedRooms.pushBack(adjacentRoom);
    }
  }
  
  for (auto visitedRoom : visitedRooms) {
    this->_fillDistanceForAdjacentRooms(visitedRoom);
  }
}

RoomPlacementData* Dungeon::_placeNewRoomAtCoordinate(Vec2 coordinate) {
  RoomPlacementData* placement = nullptr;
  
  auto alreadyPlacedRoom = this->getRoomForCoordinate(coordinate);
  auto newRoomDataSource = this->getNewRoomDataSource();
  
  if (!alreadyPlacedRoom && newRoomDataSource) {
    DungeonRoom* room = newRoomDataSource();
    
    if (room) {
      this->setRoomForCoordinate(room, coordinate);
      
      placement = RoomPlacementData::create();
      placement->setCoordinate(coordinate);
      placement->setRoom(room);
    }
  }
  
  return placement;
}
