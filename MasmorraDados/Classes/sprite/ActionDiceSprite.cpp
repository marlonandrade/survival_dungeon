//
//  ActionDiceSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#include "ActionDiceSprite.h"

#include "ActionDice.h"

USING_NS_CC;

#pragma mark - Public Interface

ActionDiceSprite* ActionDiceSprite::createWithDice(Dice *dice) {
  auto sprite = new (std::nothrow) ActionDiceSprite();
  if (sprite && sprite->initWithDice(dice)) {
    sprite->autorelease();
  } else {
    CC_SAFE_DELETE(sprite);
  }
  
  return sprite;
}

bool ActionDiceSprite::initWithDice(Dice *dice) {
  if (!DiceSprite::initWithDice(dice)) {
    return false;
  }
  
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
    this->getDice()->getState()->changeState(this->getDice());
  }
}