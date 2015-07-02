//
//  Character.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Character.h"

#include "Definitions.h"
#include "Events.h"
#include "NodeNames.h"

#include "DamageTakenData.h"

USING_NS_CC;

#pragma mark - Getter and Setter

int Character::getHitPoints() {
  return _hitPoints;
}

void Character::setHitPoints(int hitPoints) {
  if (hitPoints > CHARACTER_MAX_HP) hitPoints = CHARACTER_MAX_HP;
  
  _hitPoints = hitPoints;
  
  auto sprite = this->getSprite();
  if (sprite) {
    if (_hitPoints < 1) {
      auto dispatcher = Director::getInstance()->getEventDispatcher();
      dispatcher->dispatchCustomEvent(EVT_CHARACTER_DIED);
    } else {
      sprite->setHitPoints(_hitPoints);
    }
  }
}

#pragma mark - Public Interface

bool Character::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  this->_setupEventHandlers();
  
  return true;
}

void Character::takeDamage(int damage) {
  this->setHitPoints(this->getHitPoints() - damage);
}

void Character::heal(int amount) {
  this->setHitPoints(this->getHitPoints() + amount);
}

void Character::resetLife() {
  this->setHitPoints(CHARACTER_MAX_HP - 3);
}

bool Character::isLifeFull() {
  return this->getHitPoints() == CHARACTER_MAX_HP;
}

#pragma mark - Private Interface

void Character::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto damageTakenCallback = CC_CALLBACK_1(Character::_handleDamageTaken, this);
  this->setDamageTakenListener(
    dispatcher->addCustomEventListener(EVT_DAMAGE_TAKEN, damageTakenCallback)
  );
}

#pragma mark - Event Handlers

void Character::_handleDamageTaken(EventCustom* event) {
  auto sprite = this->getSprite();
  if (sprite) {
    auto damageTaken = (DamageTakenData*) event->getUserData();
    
    sprite->resetDamageTaken();
    
    int damage = damageTaken->getDamage();
    if (damage > 0) {
      sprite->takeDamage(damage);
    }
  }
}
