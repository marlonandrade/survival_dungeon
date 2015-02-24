//
//  ActionDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDice.h"

bool ActionDice::init() {
  if (!Dice::init()) {
    return false;
  }
  
  return true;
}

DiceFace* ActionDice::roll() {
  return nullptr;
}