//
//  MajorMonsterDice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "MajorMonsterDice.h"

#include "MonsterDiceFaceBuilder.h"

bool MajorMonsterDice::init()
{
    if (!Dice::createWithPlist("res/dice/major_monster_dice.plist",
                               MonsterDiceFaceBuilder::create())) {
        return false;
    }
    
    return true;
}