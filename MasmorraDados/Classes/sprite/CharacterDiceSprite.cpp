//
//  CharacterDiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "CharacterDiceSprite.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

bool CharacterDiceSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setHitpoints(CHARACTER_INITIAL_HP);
  this->_initializeEventListeners();
  
  return true;
}

void CharacterDiceSprite::setHitpoints(int hitpoints) {
  if (hitpoints > 6) hitpoints = 6;
  if (hitpoints < 1) hitpoints = 1;
  
  this->setTexture(this->getFileNameForHitpoints(hitpoints));
}

#pragma mark - Private Interface

void CharacterDiceSprite::_initializeEventListeners() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = [](Touch* touch, Event* event) {
    auto bounds = event->getCurrentTarget()->getBoundingBox();
    return bounds.containsPoint(touch->getLocation());
  };
  touchListener->onTouchMoved = [=](Touch* touch, Event* event) {
    this->setPosition(touch->getLocation());
    log("onTouchMoved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
  };
  touchListener->onTouchEnded = [](Touch* touch, Event* event) {
    log("onTouchEnded (%f, %f)", touch->getLocation().x, touch->getLocation().y);
  };
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

std::string CharacterDiceSprite::getFileNameForHitpoints(int hitpoints) {
  std::stringstream stream;
  stream << "images/character/" << hitpoints << ".png";
  return stream.str();
}