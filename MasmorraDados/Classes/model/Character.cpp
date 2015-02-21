//
//  Character.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Character.h"

#include "Skill.h"

USING_NS_CC;

Character* Character::createWithValueMap(cocos2d::ValueMap map) {
  auto character = new (std::nothrow) Character();
  
  if (character && character->initWithValueMap(map)) {
    character->autorelease();
  } else {
    CC_SAFE_DELETE(character);
  }
  
  return character;
}

bool Character::initWithValueMap(cocos2d::ValueMap map) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setName(map.at("name").asString());
  this->setImagePath(map.at("image").asString());
  this->setClassType(map.at("class").asString());
  
  auto initialSkillMap = map.at("initialSkill").asValueMap();
  
  this->setInitialSkill(Skill::createWithValueMap(initialSkillMap));
  
  return true;
}