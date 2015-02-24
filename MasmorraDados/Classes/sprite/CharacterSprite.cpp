//
//  CharacterSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "CharacterSprite.h"

#include "Definitions.h"

#pragma mark - Public Interface

bool CharacterSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setHitpoints(CHARACTER_INITIAL_HP);
  
  return true;
}

void CharacterSprite::setHitpoints(int hitpoints) {
  if (hitpoints > 6) hitpoints = 6;
  if (hitpoints < 1) hitpoints = 1;
  
  this->setTexture(this->getFileNameForHitpoints(hitpoints));
}

#pragma mark - Private Interface

std::string CharacterSprite::getFileNameForHitpoints(int hitpoints) {
  std::stringstream stream;
  stream << "images/character/" << hitpoints << ".png";
  return stream.str();
}