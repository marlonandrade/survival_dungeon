//
//  InitialTurn.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/22/15.
//
//

#include "InitialTurn.h"

#include "Game.h"
#include "PlayerTurn.h"

#pragma mark - Turn Methods

void InitialTurn::finish(Game *game) {
  game->setTurn(PlayerTurn::create());
}