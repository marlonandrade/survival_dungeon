//
//  RuneRoom.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __SurvivalDungeon__RuneRoom__
#define __SurvivalDungeon__RuneRoom__

#include "DungeonRoom.h"

class RuneRoom : public DungeonRoom {
public:
  CREATE_FUNC(RuneRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__SurvivalDungeon__RuneRoom__) */
