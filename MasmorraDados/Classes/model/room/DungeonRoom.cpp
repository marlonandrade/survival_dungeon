//
//  DungeonRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "DungeonRoom.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DungeonRoom::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  return true;
}

void DungeonRoom::addMonsterDice(MonsterDice *monster) {
  _monsters.pushBack(monster);
}

void DungeonRoom::removeMonsterDice(MonsterDice *monster) {
  _monsters.eraseObject(monster);
}

std::string DungeonRoom::getImagePath() {
  return nullptr;
}

bool DungeonRoom::isExplorable() {
  return false;
}