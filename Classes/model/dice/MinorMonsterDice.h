//
//  MinorMonsterDice.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __SurvivalDungeon__MinorMonsterDice__
#define __SurvivalDungeon__MinorMonsterDice__

#include "MonsterDice.h"

class MinorMonsterDice : public MonsterDice {
public:
  CREATE_FUNC(MinorMonsterDice);
  virtual bool init();
};

#endif /* defined(__SurvivalDungeon__MinorMonsterDice__) */
