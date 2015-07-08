//
//  MajorMonsterDice.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __SurvivalDungeon__MajorMonsterDice__
#define __SurvivalDungeon__MajorMonsterDice__

#include "MonsterDice.h"

class MajorMonsterDice : public MonsterDice {
public:
  CREATE_FUNC(MajorMonsterDice);
  virtual bool init();
};

#endif /* defined(__SurvivalDungeon__MajorMonsterDice__) */
