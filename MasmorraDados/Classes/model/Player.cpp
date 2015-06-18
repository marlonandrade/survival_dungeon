//
//  Player.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Player.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

bool Player::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setCharacter(Character::create());
  
  return true;
}