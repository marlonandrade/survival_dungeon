//
//  Skill.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Skill.h"

USING_NS_CC;

Skill* Skill::createWithValueMap(cocos2d::ValueMap map) {
  auto skill = new (std::nothrow) Skill();
  
  if (skill && skill->initWithValueMap(map)) {
    skill->autorelease();
  } else {
    CC_SAFE_DELETE(skill);
  }
  
  return skill;
}

bool Skill::initWithValueMap(cocos2d::ValueMap map) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setCost(map.at("cost").asString());
  this->setEffect(map.at("effect").asString());
  
  return true;
}