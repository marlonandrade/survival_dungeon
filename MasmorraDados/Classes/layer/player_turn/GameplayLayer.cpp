//
//  GameplayLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#include "GameplayLayer.h"

#include "Definitions.h"
#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "DockableContainer.h"
#include "EndTurnButton.h"
#include "FreeBootSprite.h"

#include "ActionDiceDragData.h"

#include "DiceUtil.h"
#include "OverlayUtil.h"
#include "PositionUtil.h"

#include "CommonDiceDragHandler.h"
#include "MagicDiceDragHandler.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameplayLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(PLAYER_TURN_GAMEPLAY_LAYER);
  this->setVisible(false);
  
  this->_setupChildren();
  this->_setupEventHandlers();
  
  return true;
}

void GameplayLayer::migrateDicesAndShow() {
  for (auto dice : Game::getInstance()->getActionDices()) {
    auto sprite = (ActionDiceSprite*) dice->getSprite();
    CC_SAFE_RETAIN(sprite);
    auto position = sprite->getParent()->getPosition();
    sprite->removeFromParent();
    
    auto newPosition = sprite->getPosition() + position;
    sprite->setPosition(newPosition);
    sprite->setOriginalPosition(newPosition);
    
    this->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  this->runAction(Show::create());
}

void GameplayLayer::resetFreeBootUsed() {
  this->_getFreeBootSprite()->resetFreeBootUsed();
}

void GameplayLayer::resetDockableNodes() {
  this->_getDockableContainer()->resetDockableNodes();
}

#pragma mark - Private Interface

void GameplayLayer::_setupChildren() {
  this->addChild(this->_createFreeBootSprite());
  this->addChild(this->_createDockableContainer());
  this->addChild(this->_createFinalizarButton());
}

void GameplayLayer::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto diceDragStartedCallback = CC_CALLBACK_1(GameplayLayer::_handleActionDiceDragStarted, this);
  this->setDiceDragStartedListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_STARTED, diceDragStartedCallback)
  );
  
  auto diceDragMovedCallback = CC_CALLBACK_1(GameplayLayer::_handleActionDiceDragMoved, this);
  this->setDiceDragMovedListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_MOVED, diceDragMovedCallback)
  );
  
  auto diceDragEndedCallback = CC_CALLBACK_1(GameplayLayer::_handleActionDiceDragEnded, this);
  this->setDiceDragEndedListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICE_DRAG_ENDED, diceDragEndedCallback)
  );
}

Sprite* GameplayLayer::_createFreeBootSprite() {
  auto sprite = FreeBootSprite::create();
  
  auto size = sprite->getContentSize() / 2;
  auto x = DOCK_MARGIN + size.width;
  auto y = this->getContentSize().height - (DOCK_MARGIN + size.height);
  
  sprite->setPosition(Vec2(x, y));
  
  return sprite;
}

DockableContainer* GameplayLayer::_createDockableContainer() {
  auto dockableContainer = DockableContainer::create();
  
  auto bootSprite = this->getChildByName(FREE_BOOT_SPRITE_NAME);
  auto bootSize = bootSprite->getContentSize();
  
  auto dockX = bootSprite->getPosition().x;
  auto dockY = bootSprite->getPosition().y - dockableContainer->getContentSize().height;
  
  dockableContainer->setPosition(Vec2(dockX, dockY));
  
  return dockableContainer;
}
                 
Node* GameplayLayer::_createFinalizarButton() {
  auto button = EndTurnButton::create();
  
  auto size = button->getContentSize() / 2;
  auto x = this->getContentSize().width - (END_TURN_MARGIN + size.width);
  auto y = this->getContentSize().height - (END_TURN_MARGIN + size.height);
  
  button->setPosition(Vec2(x, y));
  
  return button;
}

FreeBootSprite* GameplayLayer::_getFreeBootSprite() {
  return (FreeBootSprite*) this->getChildByName(FREE_BOOT_SPRITE_NAME);
}

DockableContainer* GameplayLayer::_getDockableContainer() {
  return (DockableContainer*) this->getChildByName(DOCK_CONTAINER_NODE_NAME);
}

#pragma mark - Event Handlers

void GameplayLayer::_handleActionDiceDragStarted(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto dice = sprite->getDice();
  
  sprite->startDragging();
  
  auto room = Game::getInstance()->getRoomForCharacterCoordinate();
  auto hasMonstersInRoom = room->getMonsters().size() > 0;
  
  if (DiceUtil::isMagicDice(dice)) {
    MagicDiceDragHandler::create()->dragStarted(data, this);
  } else if ((DiceUtil::isSwordDice(dice) ||
              DiceUtil::isBowDice(dice) ||
              DiceUtil::isShieldDice(dice)) && hasMonstersInRoom) {
    log("TEM MONSTRO NA SALA!!!!!!");
  } else {
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    CommonDiceDragHandler::create()->dragStarted(data, this, dockableContainer, dockableNodes);
  }
}

void GameplayLayer::_handleActionDiceDragMoved(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  auto dice = sprite->getDice();
  
  auto touchLocation = this->convertTouchToNodeSpace(touch);
  sprite->setPosition(touchLocation);
  
  if (DiceUtil::isMagicDice(dice)) {
    MagicDiceDragHandler::create()->dragMoved(data, this);
  } else {
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    CommonDiceDragHandler::create()->dragMoved(data, this, dockableContainer, dockableNodes);
  }
}

void GameplayLayer::_handleActionDiceDragEnded(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto dice = sprite->getDice();
  
  sprite->setLocalZOrder(sprite->getLocalZOrder() - DRAG_Z_ORDER_DELTA);
  
  OverlayUtil::removeOverlay(this);
  
  bool docked = false;
  
  if (DiceUtil::isMagicDice(dice)) {
    docked = MagicDiceDragHandler::create()->dragEnded(data, this);
  } else {
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    docked = CommonDiceDragHandler::create()->dragEnded(data, this, dockableContainer, dockableNodes);
  }
  
  if (!docked) {
    sprite->restoreOriginalPosition();
  }
}