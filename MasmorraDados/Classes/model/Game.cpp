//
//  Game.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#include "Game.h"
#include "GameOptions.h"

GameOptions& Game::getOptions()
{
    return *_options;
}

Game::Game()
{
    _options = new GameOptions();
}