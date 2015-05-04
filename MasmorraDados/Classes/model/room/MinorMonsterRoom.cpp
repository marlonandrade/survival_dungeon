//
//  MinorMonsterRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "MinorMonsterRoom.h"

#include "Images.h"

USING_NS_CC;

#pragma mark - Public Interface

void MinorMonsterRoom::initialize() {
  // sortear um monstro
  // disparar evento que novo monstro foi gerado
}

std::string MinorMonsterRoom::getImagePath() {
  return IMG_ROOM_MINOR_MONSTER;
}

bool MinorMonsterRoom::isExplorable() {
  return true;
}

