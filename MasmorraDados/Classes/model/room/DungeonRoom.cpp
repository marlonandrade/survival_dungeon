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
  
  Vector<MonsterDice*> monsters = Vector<MonsterDice*>(3);
  this->setMonsters(monsters);
  
  return true;
}

std::string DungeonRoom::getImagePath() {
  return nullptr;
}

bool DungeonRoom::isExplorable() {
  return false;
}