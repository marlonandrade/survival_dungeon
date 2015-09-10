//
//  MinorMonsterRoom.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __SurvivalDungeon__MinorMonsterRoom__
#define __SurvivalDungeon__MinorMonsterRoom__

#include "DungeonRoom.h"

class MinorMonsterRoom : public DungeonRoom {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _roomHasBeenPlacedListener,
                       RoomHasBeenPlacedListener);
  
public:
  CREATE_FUNC(MinorMonsterRoom);
  
  virtual std::string getImagePath();
  
  virtual void riseMonster();
  virtual void hasBeenPlaced(RoomPlacementData* placement);
};

#endif /* defined(__SurvivalDungeon__MinorMonsterRoom__) */
