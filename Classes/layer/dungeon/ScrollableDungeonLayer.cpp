//
//  ScrollableDungeonLayer.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/5/15.
//
//

#include "ScrollableDungeonLayer.h"

#include "NodeNames.h"

#include "BackgroundLayer.h"
#include "DungeonLayer.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ScrollableDungeonLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(SCROLLABLE_LAYER_NAME);
  
  this->_setupChildren();
  this->_setupTouchListener();
  
  return true;
}

void ScrollableDungeonLayer::resetDungeonLayer() {
  this->setPosition(Vec2::ZERO);
  this->_getDungeonLayer()->reset();
}

#pragma mark - Private Interface

void ScrollableDungeonLayer::_setupChildren() {
  this->addChild(BackgroundLayer::create(), -10);
  this->addChild(DungeonLayer::create(), 0);
}

void ScrollableDungeonLayer::_setupTouchListener() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = CC_CALLBACK_2(ScrollableDungeonLayer::_onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(ScrollableDungeonLayer::_onTouchMoved, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

DungeonLayer* ScrollableDungeonLayer::_getDungeonLayer() {
  return this->getChildByName<DungeonLayer*>(DUNGEON_LAYER_NAME);
}

bool ScrollableDungeonLayer::_onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
  return true;
}

void ScrollableDungeonLayer::_onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
  auto delta = touch->getDelta();
  
  auto currentPosition = this->getPosition();
  
  auto x = currentPosition.x + delta.x;
  auto y = currentPosition.y + delta.y;
  
  auto margin = TILE_DIMENSION * 0.5;
  
  auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  
  auto dungeon = Game::getInstance()->getDungeon();
  auto farthestCoordinates = dungeon->getFarthestCoordinates();
  
  auto initial = INITIAL_COORDINATE;
  
  auto topDelta = fabs(farthestCoordinates.top.y - initial.y);
  auto rightDelta = fabs(farthestCoordinates.right.x - initial.x);
  auto bottomDelta = fabs(farthestCoordinates.bottom.y - initial.y);
  auto leftDelta = fabs(farthestCoordinates.left.x - initial.x);
  
  auto horizontalNoScroll = visibleSize.width / 2;
  auto verticalNoScroll = visibleSize.height / 2;
  
  auto topDistance = verticalNoScroll - (topDelta * TILE_DIMENSION + TILE_DIMENSION / 2);
  auto rightDistance = horizontalNoScroll - (rightDelta * TILE_DIMENSION + TILE_DIMENSION / 2);
  auto bottomDistance = verticalNoScroll - (bottomDelta * TILE_DIMENSION + TILE_DIMENSION / 2);
  auto leftDistance = horizontalNoScroll - (leftDelta * TILE_DIMENSION + TILE_DIMENSION / 2);
  
  auto maxY = visibleOrigin.y + margin;
  auto maxX = visibleOrigin.x + margin;
  auto minY = visibleOrigin.y - margin;
  auto minX = visibleOrigin.x - margin;
  
  if (topDistance < 0) {
    minY += topDistance;
  }
  
  if (rightDistance < 0) {
    minX += rightDistance;
  }
  
  if (bottomDistance < 0) {
    maxY -= bottomDistance;
  }
  
  if (leftDistance < 0) {
    maxX -= leftDistance;
  }
  
  if (x >= maxX) x = maxX;
  if (y >= maxY) y = maxY;
  if (x <= minX) x = minX;
  if (y <= minY) y = minY;
  
  auto newPosition = Vec2(x, y);
  
  this->setPosition(newPosition);
}
