//
//  Game.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "Game.h"

bool Game::init()
{
    if (!GameObject::init()) {
        return false;
    }
    
    this->setOptions(GameOptions::create());
    this->setDungeon(Dungeon::create());
    
    return true;
}