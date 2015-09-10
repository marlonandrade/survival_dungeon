//
//  RoomPlacementData.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 25/02/2015.
//
//

#ifndef __SurvivalDungeon__RoomPlacementData__
#define __SurvivalDungeon__RoomPlacementData__

#include "GameObject.h"

#include "DungeonRoom.h"

class RoomPlacementData : public GameObject {
  CC_SYNTHESIZE_RETAIN(DungeonRoom*, _room, Room);
  CC_SYNTHESIZE(cocos2d::Vec2, _coordinate, Coordinate);
  CREATE_FUNC(RoomPlacementData);
};

#endif /* defined(__SurvivalDungeon__RoomPlacementData__) */
