//
//  DamageTakenData.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/7/15.
//
//

#ifndef __SurvivalDungeon__DamageTakenData__
#define __SurvivalDungeon__DamageTakenData__

#include "GameObject.h"

class DamageTakenData : public GameObject {
  CC_SYNTHESIZE(int, _damage, Damage);
  CREATE_FUNC(DamageTakenData);
};

#endif /* defined(__SurvivalDungeon__DamageTakenData__) */
