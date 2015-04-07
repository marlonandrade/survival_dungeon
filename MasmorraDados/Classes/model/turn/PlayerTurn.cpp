//
//  PlayerTurn.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#include "PlayerTurn.h"

#include "DungeonTurn.h"
#include "Game.h"

USING_NS_CC;

#pragma mark - Turn Methods

void PlayerTurn::execute(Game *game) {
  game->setTurn(DungeonTurn::create());
}