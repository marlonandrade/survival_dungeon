//
//  MinorMonsterDice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __MasmorraDados__MinorMonsterDice__
#define __MasmorraDados__MinorMonsterDice__

#include "MonsterDice.h"

class MinorMonsterDice : public MonsterDice {
public:
  CREATE_FUNC(MinorMonsterDice);
  virtual bool init();
};

#endif /* defined(__MasmorraDados__MinorMonsterDice__) */
