//
//  TreasureRoom.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/9/15.
//
//

#ifndef __SurvivalDungeon__TreasureRoom__
#define __SurvivalDungeon__TreasureRoom__

#include "DungeonRoom.h"

class TreasureRoom : public DungeonRoom {
public:
  CREATE_FUNC(TreasureRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__SurvivalDungeon__TreasureRoom__) */
