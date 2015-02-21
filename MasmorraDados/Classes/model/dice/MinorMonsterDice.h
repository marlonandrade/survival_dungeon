//
//  MinorMonsterDice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__MinorMonsterDice__
#define __MasmorraDados__MinorMonsterDice__

#include "Dice.h"

class MinorMonsterDice : public Dice {
public:
  virtual bool init();
  CREATE_FUNC(MinorMonsterDice);
};

#endif /* defined(__MasmorraDados__MinorMonsterDice__) */
