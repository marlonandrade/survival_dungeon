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

class MonsterDice : public Dice {
  CC_SYNTHESIZE(bool, _movedThisTurn, MovedThisTurn);
};

#endif /* defined(__MasmorraDados__MonsterDice__) */
