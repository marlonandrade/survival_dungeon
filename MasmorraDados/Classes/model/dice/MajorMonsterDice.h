//
//  MajorMonsterDice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/3/15.
//
//

#ifndef __MasmorraDados__MajorMonsterDice__
#define __MasmorraDados__MajorMonsterDice__

#include "MonsterDice.h"

class MajorMonsterDice : public MonsterDice {
public:
  CREATE_FUNC(MajorMonsterDice);
  virtual bool init();
};

#endif /* defined(__MasmorraDados__MajorMonsterDice__) */
