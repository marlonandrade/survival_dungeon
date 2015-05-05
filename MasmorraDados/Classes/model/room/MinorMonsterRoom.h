//
//  MinorMonsterRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __MasmorraDados__MinorMonsterRoom__
#define __MasmorraDados__MinorMonsterRoom__

#include "DungeonRoom.h"

class MinorMonsterRoom : public DungeonRoom {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _roomHasBeenPlacedListener,
                       RoomHasBeenPlacedListener);
  
public:
  CREATE_FUNC(MinorMonsterRoom);
  virtual bool init();
  
  virtual std::string getImagePath();
  virtual bool isExplorable();
  
private:
#pragma mark - Events
  void _handleRoomHasBeenPlaced(cocos2d::EventCustom* event);
};

#endif /* defined(__MasmorraDados__MinorMonsterRoom__) */
