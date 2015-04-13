//
//  ActionDiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#include "ActionDiceSprite.h"

#include "ActionDice.h"
#include "ActionDiceState.h"
#include "ActionDiceStateNormal.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setTexture(this->_getFileNameForDice(nullptr));
  this->setDiceState(ActionDiceStateNormal::create());
  this->_setupTouchListener();
  
  return true;
}

#pragma mark - Private Interface

void ActionDiceSprite::_setupTouchListener() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->setSwallowTouches(true);
  touchListener->onTouchBegan = CC_CALLBACK_2(ActionDiceSprite::_onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(ActionDiceSprite::_onTouchMoved, this);
  touchListener->onTouchEnded = CC_CALLBACK_2(ActionDiceSprite::_onTouchEnded, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

std::string ActionDiceSprite::_getFileNameForDice(ActionDice* dice) {
  return "images/dice/sword.png";
}

#pragma mark Touch Events

bool ActionDiceSprite::_onTouchBegan(Touch* touch, Event* event) {
  auto target = event->getCurrentTarget();
  auto layer = target->getParent();
  
  auto bounds = target->getBoundingBox();
  auto touchLocation = layer->convertTouchToNodeSpace(touch);
  
  return bounds.containsPoint(touchLocation);
}

void ActionDiceSprite::_onTouchMoved(Touch* touch, Event* event) {
}

void ActionDiceSprite::_onTouchEnded(Touch* touch, Event* event) {
  auto target = event->getCurrentTarget();
  auto layer = target->getParent();
  
  auto bounds = target->getBoundingBox();
  auto touchLocation = layer->convertTouchToNodeSpace(touch);
  
  auto touchInSprite = bounds.containsPoint(touchLocation);
  
  if (touchInSprite) {
    this->getDiceState()->changeState(this);
  }
}