//
//  Game.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__Game__
#define __MasmorraDados__Game__

#include "cocos2d.h"

#include "Dungeon.h"
#include "DungeonRoom.h"
#include "GameObject.h"

class Game : public GameObject {
  CC_SYNTHESIZE_RETAIN(Dungeon*, _dungeon, Dungeon);
  CC_SYNTHESIZE(cocos2d::Vector<DungeonRoom*>, _availableRooms, AvailableRooms);
  CC_SYNTHESIZE(RoomPlacedDelegate, _roomPlacedDelegate, RoomPlacedDelegate);
protected:
  cocos2d::Vec2 _characterPosition;
public:
  virtual cocos2d::Vec2 getCharacterPosition(void) const { return _characterPosition; }
  virtual void setCharacterPosition(cocos2d::Vec2 position);
  
public:
  static Game* createWithRoomPlacedDelegate(RoomPlacedDelegate delegate);
  virtual bool initWithRoomPlacedDelegate(RoomPlacedDelegate delegate);
  CREATE_FUNC(Game);
  
private:
  void _setupInitialPosition(RoomPlacedDelegate delegate);
  void _setupAvaiableRooms();
  
  DungeonRoom* _pickRandomRoom();
  void _placeAdjacentTiles();
};

#endif /* defined(__MasmorraDados__Game__) */
