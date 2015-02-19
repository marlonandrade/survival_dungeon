//
//  MinorMonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "MinorMonsterDice.h"

#include "MonsterDiceFaceBuilder.h"

bool MinorMonsterDice::init()
{
    if (!Dice::createWithPlist("res/dice/minor_monster_dice.plist",
                               MonsterDiceFaceBuilder::create())) {
        return false;
    }
    
    return true;
}