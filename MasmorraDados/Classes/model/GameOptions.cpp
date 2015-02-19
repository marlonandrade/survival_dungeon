//
//  GameOptions.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "GameOptions.h"
#include "Definitions.h"

bool GameOptions::init()
{
    if (!GameObject::init()) {
        return false;
    }
    
    this->setRequiredXpToWin(XP_TO_WIN_MIN);
    
    return true;
}