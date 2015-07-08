//
//  DungeonTurn.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __SurvivalDungeon__DungeonTurn__
#define __SurvivalDungeon__DungeonTurn__

#include "Turn.h"

class DungeonTurn : public Turn {
public:
  CREATE_FUNC(DungeonTurn);
  
  virtual void execute(Game* game);
  virtual void finish(Game* game);
};

#endif /* defined(__SurvivalDungeon__DungeonTurn__) */
