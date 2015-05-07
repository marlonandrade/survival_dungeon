//
//  DungeonTurn.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#include "DungeonTurn.h"

#include "Game.h"
#include "PlayerTurn.h"

#pragma mark - Turn Methods

void DungeonTurn::execute(Game *game) {
  game->getDungeon()->moveMonsters();
  game->getDungeon()->riseMonsters();
}

void DungeonTurn::finish(Game *game) {
  game->setTurn(PlayerTurn::create());
}