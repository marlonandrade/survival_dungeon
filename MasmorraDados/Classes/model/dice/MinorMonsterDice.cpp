//
//  MinorMonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "MinorMonsterDice.h"

bool MinorMonsterDice::init()
{
    if (!Dice::createWithPlist("res/dice/minor_monster.plist")) {
        return false;
    }
    
    return true;
}