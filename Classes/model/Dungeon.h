//
//  Dungeon.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __SurvivalDungeon__Dungeon__
#define __SurvivalDungeon__Dungeon__

#include "GameObject.h"

#include "Definitions.h"
#include "DungeonRoom.h"
#include "RoomPlacementData.h"

typedef cocos2d::Map<int, DungeonRoom*> DungeonGrid;
typedef std::function<DungeonRoom* (void)> NewRoomDataSource;

struct FarthestCoordinates {
  cocos2d::Vec2 top;
  cocos2d::Vec2 right;
  cocos2d::Vec2 bottom;
  cocos2d::Vec2 left;
};

class Dungeon : public GameObject {
private:
  DungeonGrid _rooms;
  FarthestCoordinates _farthestCoordinates;
  CC_SYNTHESIZE(NewRoomDataSource, _newRoomDataSource, NewRoomDataSource);
  
public:
  virtual bool init();
  CREATE_FUNC(Dungeon);
  
  void placeInitialRoom();
  
  void moveMonsters();
  void riseMonsters();
  void resetMonsterMovedState();
  
  DungeonRoom* getRoomForCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getCoordinateForRoom(DungeonRoom* room);
  
  DungeonRoom* getInitialRoom();
  FarthestCoordinates getFarthestCoordinates();
  
  void removeDamageDealtToMonsters();
  
  void placeRoomsAdjacentTo(cocos2d::Vec2 coordinate);
  void calculateRoomDistanceToPlayer(cocos2d::Vec2 playerCoordinate);
private:
  void _adjustFarthestCoordinates(cocos2d::Vec2 newCoordinate);
  void _resetDistanceToPlayer();
  void _fillDistanceForAdjacentRooms(DungeonRoom* room);
  void _moveMonstersForAdjacentRooms(DungeonRoom* room);
  
  RoomPlacementData* _placeRoomAtCoordinate(DungeonRoom* room, cocos2d::Vec2 coordinate);
  RoomPlacementData* _placeNewRoomAtCoordinate(cocos2d::Vec2 coordinate);
};

#endif /* defined(__SurvivalDungeon__Dungeon__) */
