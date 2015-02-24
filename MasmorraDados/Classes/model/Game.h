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
protected:
  cocos2d::Vec2 _playerPosition;
public:
  virtual cocos2d::Vec2 getPlayerPosition(void) const { return _playerPosition; }
  virtual void setPlayerPosition(cocos2d::Vec2 position);
  
public:
  virtual bool init();
  CREATE_FUNC(Game);
  
  
private:
  void _setupInitialPosition();
  void _setupAvaiableRooms();
  
  DungeonRoom* _pickRandomRoom();
  void _placeAdjacentTiles();
};

#endif /* defined(__MasmorraDados__Game__) */
