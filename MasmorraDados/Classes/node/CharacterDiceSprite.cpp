//
//  CharacterDiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "CharacterDiceSprite.h"

#include "Definitions.h"
#include "Events.h"
#include "NodeNames.h"

#include "FileUtil.h"

USING_NS_CC;

#pragma mark - Getter

int CharacterDiceSprite::getDamageTaken() {
  return _damageTaken;
}

#pragma mark - Setter

void CharacterDiceSprite::setDamageTaken(int damage) {
  if (damage < 0) damage = 0;
  
  _damageTaken = damage;
  
  auto damageTakenSprite = this->getChildByName(DAMAGE_TAKEN_SPRITE_NAME);
  if (damageTakenSprite) {
    damageTakenSprite->removeFromParent();
  }
  
  if (damage > 0) {
    auto fileName = FileUtil::damageFileName(damage);
    damageTakenSprite = Sprite::create(fileName);
    damageTakenSprite->setName(DAMAGE_TAKEN_SPRITE_NAME);
    
    auto size = this->getContentSize() - Size(2, 2);
    damageTakenSprite->setPosition(Vec2(size));
    
    this->addChild(damageTakenSprite);
  }
}

#pragma mark - Public Interface

bool CharacterDiceSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setName(CHARACTER_DICE_SPRITE_NAME);
  
  this->_setupTouchListener();
  
  return true;
}

void CharacterDiceSprite::setHitPoints(int hitPoints) {
  auto imageName = FileUtil::characterFileName(hitPoints);
  this->setTexture(imageName);
}

void CharacterDiceSprite::resetDamageTaken() {
  this->setDamageTaken(0);
}

void CharacterDiceSprite::takeDamage(int damage) {
  this->setDamageTaken(damage);
}

void CharacterDiceSprite::defendDamage(int damage) {
  this->setDamageTaken(this->getDamageTaken() - damage);
}

#pragma mark - Private Interface

void CharacterDiceSprite::_setupTouchListener() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->setSwallowTouches(true);
  touchListener->onTouchBegan = CC_CALLBACK_2(CharacterDiceSprite::_onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(CharacterDiceSprite::_onTouchMoved, this);
  touchListener->onTouchEnded = CC_CALLBACK_2(CharacterDiceSprite::_onTouchEnded, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

#pragma mark - Touch Events

bool CharacterDiceSprite::_onTouchBegan(Touch *touch, Event *event) {
  auto target = event->getCurrentTarget();
  auto layer = target->getParent();
  
  auto bounds = target->getBoundingBox();
  auto touchLocation = layer->convertTouchToNodeSpace(touch);
  
  auto touchInSprite = bounds.containsPoint(touchLocation);
  
  auto canMove = touchInSprite && this->getDelegate()->canCharacterMove();
  
  if (canMove) {
    this->getDelegate()->characterWillMove(this);
  }
  
  return canMove;
}

void CharacterDiceSprite::_onTouchMoved(Touch *touch, Event *event) {
  auto target = event->getCurrentTarget();
  auto layer = target->getParent();
  
  auto bounds = target->getBoundingBox();
  auto touchLocation = layer->convertTouchToNodeSpace(touch);
  
  this->setPosition(touchLocation);
  
  auto dungeonLayer = layer->getParent();
  auto position = dungeonLayer->convertTouchToNodeSpace(touch);
  
  this->getDelegate()->characterIsMovingToLocation(position);
}

void CharacterDiceSprite::_onTouchEnded(Touch *touch, Event *event) {
  auto target = event->getCurrentTarget();
  auto dungeonLayer = target->getParent()->getParent();
  
  auto position = dungeonLayer->convertTouchToNodeSpace(touch);
  
  bool characterMoved = this->getDelegate()->canCharacterMoveToLocation(position);
  
  if (characterMoved) {
    this->getDelegate()->characterMovedToLocation(this, position);
  } else {
    this->getDelegate()->characterDidNotMove(this);
  }
}