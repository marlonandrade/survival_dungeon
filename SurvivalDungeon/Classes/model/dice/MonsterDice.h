//
//  MonsterDice.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __SurvivalDungeon__MonsterDice__
#define __SurvivalDungeon__MonsterDice__

#include "Dice.h"

typedef enum {
  CombatModeMelee,
  CombatModeRanged
} CombatMode;

class MonsterDice : public Dice {
public:
  CC_SYNTHESIZE(bool, _movedThisTurn, MovedThisTurn);
  CC_SYNTHESIZE(bool, _rangedCombat, RangedCombat);
  
  CC_PROPERTY(int, _hitPoints, HitPoints);
  
  void takeDamage(int damage, CombatMode combatMode);
  void resetLife();
  
  void roll();
};

#endif /* defined(__SurvivalDungeon__MonsterDice__) */
