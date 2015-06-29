//
//  MonsterDice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __MasmorraDados__MonsterDice__
#define __MasmorraDados__MonsterDice__

#include "Dice.h"

typedef enum {
  CombatModeMelee,
  CombatModeRanged
} CombatMode;

class MonsterDice : public Dice {
public:
  CC_SYNTHESIZE(bool, _movedThisTurn, MovedThisTurn);
  CC_SYNTHESIZE(bool, _meleeCombat, MeleeCombat);
  
  CC_PROPERTY(int, _hitPoints, HitPoints);
  
  void takeDamage(int damage, CombatMode combatMode);
  void resetLife();
};

#endif /* defined(__MasmorraDados__MonsterDice__) */
