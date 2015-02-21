//
//  ActionDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDice.h"

#include "ActionDiceFaceBuilder.h"

bool ActionDice::init() {
  if (!Dice::initWithPlist("res/dice/action_dice.plist",
                           ActionDiceFaceBuilder::create())) {
    return false;
  }
  
  return true;
}