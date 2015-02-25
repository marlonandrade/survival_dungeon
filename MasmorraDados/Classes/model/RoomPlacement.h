//
//  RoomPlacement.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 25/02/2015.
//
//

#ifndef __MasmorraDados__RoomPlacement__
#define __MasmorraDados__RoomPlacement__

#include "GameObject.h"

class DungeonRoom;

class RoomPlacement : public GameObject {
  CC_SYNTHESIZE(DungeonRoom*, _room, Room);
  CC_SYNTHESIZE(cocos2d::Vec2, _position, Position);
  CREATE_FUNC(RoomPlacement);
};

#endif /* defined(__MasmorraDados__RoomPlacement__) */
