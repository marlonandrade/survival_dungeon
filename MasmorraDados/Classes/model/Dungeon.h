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
#include "RoomPlacement.h"

typedef cocos2d::Map<int, DungeonRoom*> DungeonGrid;
typedef std::function<void (cocos2d::Vector<RoomPlacement*>)> RoomPlacedDelegate;
typedef std::function<DungeonRoom* (void)> NewRoomDataSource;

class Dungeon : public GameObject {
private:
  DungeonGrid _rooms;
  CC_SYNTHESIZE(RoomPlacedDelegate, _roomPlacedDelegate, RoomPlacedDelegate);
  CC_SYNTHESIZE(NewRoomDataSource, _newRoomDataSource, NewRoomDataSource);
  
  cocos2d::Vec2 _topMostRoomPosition;
  cocos2d::Vec2 _rightMostRoomPosition;
  cocos2d::Vec2 _bottomMostRoomPosition;
  cocos2d::Vec2 _leftMostRoomPosition;
  
public:
  virtual bool init();
  CREATE_FUNC(Dungeon);
  
  void moveMonsters();
  void riseMonsters();
  
  void setRoomForPosition(DungeonRoom* room, cocos2d::Vec2 position);
  DungeonRoom* getRoomForPosition(cocos2d::Vec2 position);
  
  DungeonRoom* getInitialRoom();
  
  void placeRoomsAdjacentTo(cocos2d::Vec2 position);
  void calculateRoomDistanceToPlayer(cocos2d::Vec2 playerPosition);
  
  std::vector<cocos2d::Vec2> adjacentPositionsTo(cocos2d::Vec2 position);
  
  std::string nameForPosition(cocos2d::Vec2 position);
  int indexForPosition(cocos2d::Vec2 position);
  cocos2d::Vec2 positionForIndex(int index);
  
  void setTopMostRoomPosition(cocos2d::Vec2 position);
  cocos2d::Vec2 getTopMostRoomPosition();
  
  void setRightMostRoomPosition(cocos2d::Vec2 position);
  cocos2d::Vec2 getRightMostRoomPosition();
  
  void setBottomMostRoomPosition(cocos2d::Vec2 position);
  cocos2d::Vec2 getBottomMostRoomPosition();
  
  void setLeftMostRoomPosition(cocos2d::Vec2 position);
  cocos2d::Vec2 getLeftMostRoomPosition();
private:
  RoomPlacement* _placeNewRoomAtPosition(cocos2d::Vec2 position);
};

#endif /* defined(__MasmorraDados__Dungeon__) */
