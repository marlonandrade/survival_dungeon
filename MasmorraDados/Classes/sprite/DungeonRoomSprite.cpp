//
//  DungeonRoomSprite.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/31/15.
//
//

#include "DungeonRoomSprite.h"

#include "Definitions.h"

#include "DungeonRoom.h"

#include "CoordinateUtil.h"
#include "PositionUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

DungeonRoomSprite* DungeonRoomSprite::createWithRoom(DungeonRoom *room) {
  auto sprite = new (std::nothrow) DungeonRoomSprite();
  if (sprite && sprite->initWithRoom(room)) {
    sprite->autorelease();
  } else {
    CC_SAFE_DELETE(sprite);
  }
  return sprite;
}

bool DungeonRoomSprite::initWithRoom(DungeonRoom *room) {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setTexture(room->getImagePath());
  
  return true;
}

void DungeonRoomSprite::setCoordinate(Vec2 coordinate) {
  this->setName(CoordinateUtil::nameForCoordinate(coordinate));
  this->setPosition(PositionUtil::positionForCoordinate(coordinate));
}

void DungeonRoomSprite::addDice(Dice *dice) {
  auto diceSprite = dice->getSprite();
  diceSprite->setPosition(PositionUtil::centerOfNode(this));
  this->addChild(diceSprite);
  this->adjustChildren();
}

void DungeonRoomSprite::adjustChildren() {
  auto roomCenter = PositionUtil::centerOfNode(this);
  
  auto sprites = this->getChildren();
  switch (sprites.size()) {
    case 1: {
      auto sprite1 = sprites.at(0);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, roomCenter);
      sprite1->runAction(moveSprite1);
    } break;
    case 2: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), 0);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, 0);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
    } break;
    case 3: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      auto h = sprite1->getContentSize().height / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), h + 1);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      h = sprite2->getContentSize().height / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, h + 1);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
      
      auto sprite3 = sprites.at(2);
      
      h = sprite3->getContentSize().height / 2;
      
      auto sprite3NewPosition = roomCenter + Vec2(0, -(h + 1));
      auto moveSprite3 = MoveTo::create(MOVE_DICE_DURATION, sprite3NewPosition);
      sprite3->runAction(moveSprite3);
    } break;
    case 4: {
      auto sprite1 = sprites.at(0);
      
      auto w = sprite1->getContentSize().width / 2;
      auto h = sprite1->getContentSize().height / 2;
      
      auto sprite1NewPosition = roomCenter + Vec2(-(w + 1), h + 1);
      auto moveSprite1 = MoveTo::create(MOVE_DICE_DURATION, sprite1NewPosition);
      sprite1->runAction(moveSprite1);
      
      auto sprite2 = sprites.at(1);
      
      w = sprite2->getContentSize().width / 2;
      h = sprite2->getContentSize().height / 2;
      
      auto sprite2NewPosition = roomCenter + Vec2(w + 1, h + 1);
      auto moveSprite2 = MoveTo::create(MOVE_DICE_DURATION, sprite2NewPosition);
      sprite2->runAction(moveSprite2);
      
      auto sprite3 = sprites.at(2);
      
      w = sprite3->getContentSize().width / 2;
      h = sprite3->getContentSize().height / 2;
      
      auto sprite3NewPosition = roomCenter + Vec2(-(w + 1), -(h + 1));
      auto moveSprite3 = MoveTo::create(MOVE_DICE_DURATION, sprite3NewPosition);
      sprite3->runAction(moveSprite3);
      
      auto sprite4 = sprites.at(3);
      
      w = sprite4->getContentSize().width / 2;
      h = sprite4->getContentSize().height / 2;
      
      auto sprite4NewPosition = roomCenter + Vec2(w + 1, -(h + 1));
      auto moveSprite4 = MoveTo::create(MOVE_DICE_DURATION, sprite4NewPosition);
      sprite4->runAction(moveSprite4);
    } break;
  }
}

bool DungeonRoomSprite::canCharacterMoveToLocation(Vec2 location) {
  return this->getBoundingBox().containsPoint(location);
}