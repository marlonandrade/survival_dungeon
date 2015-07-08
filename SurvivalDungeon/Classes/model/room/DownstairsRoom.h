//
//  DownstairsRoom.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/9/15.
//
//

#ifndef __SurvivalDungeon__DownstairsRoom__
#define __SurvivalDungeon__DownstairsRoom__

#include "DungeonRoom.h"

class DownstairsRoom : public DungeonRoom {
public:
  CREATE_FUNC(DownstairsRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__SurvivalDungeon__DownstairsRoom__) */
