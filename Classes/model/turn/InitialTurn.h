//
//  InitialTurn.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/22/15.
//
//

#ifndef __SurvivalDungeon__InitialTurn__
#define __SurvivalDungeon__InitialTurn__

#include "Turn.h"

class InitialTurn : public Turn {
public:
  CREATE_FUNC(InitialTurn);
  
  virtual void finish(Game* game);
};

#endif /* defined(__SurvivalDungeon__InitialTurn__) */
