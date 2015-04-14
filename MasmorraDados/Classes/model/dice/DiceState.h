//
//  DiceState.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __MasmorraDados__DiceState__
#define __MasmorraDados__DiceState__

#include "GameObject.h"

class Dice;

class DiceState : public GameObject {
public:
  virtual bool canChangeState() = 0;
  virtual void changeState(Dice* dice) = 0;
};

#endif /* defined(__MasmorraDados__DiceState__) */
