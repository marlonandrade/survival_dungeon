//
//  MonsterKilledData.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/30/15.
//
//

#ifndef __SurvivalDungeon__MonsterKilledData__
#define __SurvivalDungeon__MonsterKilledData__

#include "GameObject.h"

#include "MonsterDice.h"

class MonsterKilledData : public GameObject {
  CC_SYNTHESIZE_RETAIN(MonsterDice*, _monsterDice, MonsterDice);
  
  CREATE_FUNC(MonsterKilledData);
};

#endif /* defined(__SurvivalDungeon__MonsterKilledData__) */
