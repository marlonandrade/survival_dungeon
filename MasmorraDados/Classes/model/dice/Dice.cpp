//
//  Dice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dice.h"

#include "DiceFace.h"

USING_NS_CC;

DiceFace* Dice::roll() {
  return this->getFaces().getRandomObject();
}
