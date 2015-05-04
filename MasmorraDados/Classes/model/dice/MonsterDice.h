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
public:
  static MonsterDice* createWithFaces(DiceFaces faces);
  virtual bool initWithFaces(DiceFaces faces);
  
  static MonsterDice* createMinorMonsterDice();
  static MonsterDice* createMajorMonsterDice();
};

#endif /* defined(__MasmorraDados__MonsterDice__) */
