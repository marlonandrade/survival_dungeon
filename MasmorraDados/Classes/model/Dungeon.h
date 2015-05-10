//
//  Dungeon.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Dungeon__
#define __MasmorraDados__Dungeon__

#include "GameObject.h"

#include "Definitions.h"
#include "DungeonRoom.h"
#include "RoomPlacementData.h"

typedef cocos2d::Map<int, DungeonRoom*> DungeonGrid;
typedef std::function<void (cocos2d::Vector<RoomPlacementData*>)> RoomPlacedDelegate;
typedef std::function<DungeonRoom* (void)> NewRoomDataSource;

class Dungeon : public GameObject {
private:
  DungeonGrid _rooms;
  CC_SYNTHESIZE(RoomPlacedDelegate, _roomPlacedDelegate, RoomPlacedDelegate);
  CC_SYNTHESIZE(NewRoomDataSource, _newRoomDataSource, NewRoomDataSource);
  
  cocos2d::Vec2 _topMostRoomCoordinate;
  cocos2d::Vec2 _rightMostRoomCoordinate;
  cocos2d::Vec2 _bottomMostRoomCoordinate;
  cocos2d::Vec2 _leftMostRoomCoordinate;
  
public:
  virtual bool init();
  CREATE_FUNC(Dungeon);
  
  void moveMonsters();
  void riseMonsters();
  
  void setRoomForCoordinate(DungeonRoom* room, cocos2d::Vec2 coordinate);
  DungeonRoom* getRoomForCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getCoordinateForRoom(DungeonRoom* room);
  
  DungeonRoom* getInitialRoom();
  
  void placeRoomsAdjacentTo(cocos2d::Vec2 coordinate);
  void calculateRoomDistanceToPlayer(cocos2d::Vec2 playerCoordinate);
  
  std::vector<cocos2d::Vec2> adjacentCoordinatesTo(cocos2d::Vec2 coordinate);
  
  std::string nameForCoordinate(cocos2d::Vec2 coordinate);
  int indexForCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 coordinateForIndex(int index);
  
  void setTopMostRoomCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getTopMostRoomCoordinate();
  
  void setRightMostRoomCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getRightMostRoomCoordinate();
  
  void setBottomMostRoomCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getBottomMostRoomCoordinate();
  
  void setLeftMostRoomCoordinate(cocos2d::Vec2 coordinate);
  cocos2d::Vec2 getLeftMostRoomCoordinate();
private:
  void _resetDistanceToPlayer();
  void _fillDistanceForAdjacentRooms(DungeonRoom* room);
  
  RoomPlacementData* _placeNewRoomAtCoordinate(cocos2d::Vec2 coordinate);
};

#endif /* defined(__MasmorraDados__Dungeon__) */
