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
  
  this->setTopMostRoomCoordinate(INITIAL_COORDINATE);
  this->setRightMostRoomCoordinate(INITIAL_COORDINATE);
  this->setBottomMostRoomCoordinate(INITIAL_COORDINATE);
  this->setLeftMostRoomCoordinate(INITIAL_COORDINATE);
  
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
      auto adjacentCoordinates = this->adjacentCoordinatesTo(coordinate);
      
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
  auto index = CoordinateUtil::indexForCoordinate(coordinate);
  
  if (coordinate.y > this->getTopMostRoomCoordinate().y) {
    this->setTopMostRoomCoordinate(coordinate);
  }
  
  if (coordinate.x > this->getRightMostRoomCoordinate().x) {
    this->setRightMostRoomCoordinate(coordinate);
  }
  
  if (coordinate.y < this->getBottomMostRoomCoordinate().y) {
    this->setBottomMostRoomCoordinate(coordinate);
  }
  
  if (coordinate.x < this->getLeftMostRoomCoordinate().x) {
    this->setLeftMostRoomCoordinate(coordinate);
  }
  
  _rooms.insert(index, room);
}

DungeonRoom* Dungeon::getRoomForCoordinate(Vec2 coordinate) {
  auto index = CoordinateUtil::indexForCoordinate(coordinate);
  return _rooms.at(index);
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
  
  for (Vec2 adjacentCoordinate : this->adjacentCoordinatesTo(coordinate)) {
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

std::vector<Vec2> Dungeon::adjacentCoordinatesTo(Vec2 coordinate) {
  std::vector<Vec2> adjacentCoordinates;
  
  auto top = coordinate + Vec2::UNIT_Y;
  adjacentCoordinates.push_back(top);
  
  auto right = coordinate + Vec2::UNIT_X;
  adjacentCoordinates.push_back(right);
  
  auto bottom = coordinate - Vec2::UNIT_Y;
  adjacentCoordinates.push_back(bottom);
  
  auto left = coordinate - Vec2::UNIT_X;
  adjacentCoordinates.push_back(left);
  
  return adjacentCoordinates;
}

void Dungeon::setTopMostRoomCoordinate(Vec2 coordinate) {
  _topMostRoomCoordinate = coordinate;
}

Vec2 Dungeon::getTopMostRoomCoordinate() {
  return _topMostRoomCoordinate;
}

void Dungeon::setRightMostRoomCoordinate(Vec2 coordinate) {
  _rightMostRoomCoordinate = coordinate;
}

Vec2 Dungeon::getRightMostRoomCoordinate() {
  return _rightMostRoomCoordinate;
}

void Dungeon::setBottomMostRoomCoordinate(Vec2 coordinate) {
  _bottomMostRoomCoordinate = coordinate;
}

Vec2 Dungeon::getBottomMostRoomCoordinate() {
  return _bottomMostRoomCoordinate;
}

void Dungeon::setLeftMostRoomCoordinate(Vec2 coordinate) {
  _leftMostRoomCoordinate = coordinate;
}

Vec2 Dungeon::getLeftMostRoomCoordinate() {
  return _leftMostRoomCoordinate;
}

#pragma mark - Private Interface

void Dungeon::_resetDistanceToPlayer() {
  for (auto room : this->_rooms) {
    auto dungeonRoom = std::get<1>(room);
    dungeonRoom->setDistanceToPlayer(NOT_CALCULATED_DISTANCE);
  }
}

void Dungeon::_fillDistanceForAdjacentRooms(DungeonRoom *room) {
  Vector<DungeonRoom*> visitedRooms;
  
  auto coordinates = this->adjacentCoordinatesTo(room->getCoordinate());
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
