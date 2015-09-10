//
//  InitialRoom.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#ifndef __SurvivalDungeon__InitialRoom__
#define __SurvivalDungeon__InitialRoom__

#include "DungeonRoom.h"

class InitialRoom : public DungeonRoom {
public:
  CREATE_FUNC(InitialRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__SurvivalDungeon__InitialRoom__) */
