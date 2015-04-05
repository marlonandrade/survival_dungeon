//
//  ScrollableLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/5/15.
//
//

#include "ScrollableLayer.h"

#include "Definitions.h"

USING_NS_CC;

ScrollableLayer* ScrollableLayer::createWithDungeon(Dungeon* dungeon) {
  auto layer = new (std::nothrow) ScrollableLayer();
  
  if (layer && layer->initWithDungeon(dungeon)) {
    layer->autorelease();
  } else {
    CC_SAFE_DELETE(layer);
  }
  
  return layer;
}

bool ScrollableLayer::initWithDungeon(Dungeon *dungeon) {
  if (!Layer::init()) {
    return false;
  }
  
  this->setDungeon(dungeon);
  this->_setupTouchListener();
  
  return true;
}

void ScrollableLayer::_setupTouchListener() {
  this->setTag(SCROLLABLE_LAYER_TAG);
  
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = CC_CALLBACK_2(ScrollableLayer::_onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(ScrollableLayer::_onTouchMoved, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool ScrollableLayer::_onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
  return true;
}

void ScrollableLayer::_onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
  auto delta = touch->getDelta();
  
  auto currentPosition = this->getPosition();
  
  auto x = currentPosition.x + delta.x;
  auto y = currentPosition.y + delta.y;
  
  auto margin = TILE_DIMENSION * 0.5;
  
  auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  
  auto top = this->getDungeon()->getTopMostRoomPosition();
  auto right = this->getDungeon()->getRightMostRoomPosition();
  auto bottom = this->getDungeon()->getBottomMostRoomPosition();
  auto left = this->getDungeon()->getLeftMostRoomPosition();
  
  auto initial = INITIAL_POSITION;
  
  auto topDelta = abs(top.y - initial.y);
  auto rightDelta = abs(right.x - initial.x);
  auto bottomDelta = abs(bottom.y - initial.y);
  auto leftDelta = abs(left.x - initial.x);
  
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