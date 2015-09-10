//
//  FreeBootSprite.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "FreeBootSprite.h"

#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

USING_NS_CC;

#pragma mark - Public Interface

bool FreeBootSprite::init() {
  if (!Sprite::init()) {
    return false;
  }
  
  this->setTexture(IMG_DICE_ACTION_FREE_BOOT);
  this->setName(FREE_BOOT_SPRITE_NAME);
  
  this->_setupEventHandlers();
  
  return true;
}

void FreeBootSprite::resetFreeBootUsed() {
  this->removeAllChildren();
}

#pragma mark - Private Interface

void FreeBootSprite::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto freeBootSpentCallback = CC_CALLBACK_1(FreeBootSprite::_handleActionFreeBootSpent, this);
  this->setFreeBootSpentListener(
    dispatcher->addCustomEventListener(EVT_ACTION_FREE_BOOT_SPENT, freeBootSpentCallback)
  );
}

#pragma mark - Event Handlers

void FreeBootSprite::_handleActionFreeBootSpent(EventCustom* event) {
  auto spentActionSprite = Sprite::create(IMG_DICE_ACTION_SPENT);
  spentActionSprite->setPosition(Vec2(this->getContentSize().width / 2,
                                      this->getContentSize().height / 2));
  this->addChild(spentActionSprite);
}
