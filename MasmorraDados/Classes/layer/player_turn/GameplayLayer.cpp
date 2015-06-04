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
#include "FreeBootSprite.h"

#include "ActionDiceDragData.h"

#include "DiceUtil.h"
#include "PositionUtil.h"

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
  auto button = ui::Button::create(IMG_BUTTON_END_TURN_NORMAL,
                                   IMG_BUTTON_END_TURN_SELECTED,
                                   IMG_BUTTON_END_TURN_DISABLED);
  button->setName(END_TURN_BUTTON_NAME);
  button->addTouchEventListener(CC_CALLBACK_2(GameplayLayer::_handleEndTurnTouched, this));
  
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

void GameplayLayer::_triggerMagicDiceOnTargetDice(Dice *targetDice) {
  log("permitir mudar a face do dado");
  
  auto sprite = targetDice->getSprite();
  auto nodePosition = sprite->getPosition();
  
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  std::vector<std::string> images;
  
  images.push_back(IMG_DICE_ACTION_BOOT);
  images.push_back(IMG_DICE_ACTION_BOW);
  images.push_back(IMG_DICE_ACTION_HEAL);
  images.push_back(IMG_DICE_ACTION_SHIELD);
  images.push_back(IMG_DICE_ACTION_SWORD);
  
  int position = 0;
  for (auto image : images) {
    if (image != targetDice->getSelectedFace()->getImagePath()) {
      auto sprite = Sprite::create(image);
      sprite->setPosition(nodePosition);
      
      this->addChild(sprite);
      
      targetNodes.pushBack(sprite);
      
      auto yOffset = (sprite->getContentSize().height + 2) * (position + 1);
      auto newPosition = Vec2(nodePosition.x, nodePosition.y + yOffset);
      
      auto delay = DelayTime::create(MAGIC_DICE_DURATION * position);
      auto adjustPosition = EaseOut::create(MoveTo::create(MAGIC_DICE_DURATION, newPosition), 5);
      
      sprite->runAction(Sequence::create(delay, adjustPosition, NULL));
      
      position++;
    }
  }
  
  auto delay = DelayTime::create(OVERLAY_DURATION);
  auto callfunc = CallFunc::create([=] {
    this->_addOverlay(targetNodes);
  });
  
  this->runAction(Sequence::create(delay, callfunc, NULL));
}

void GameplayLayer::_addOverlay(Vector<Node*> targetNodes) {
  auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
  overlayLayer->setName(OVERLAY_LAYER_NAME);
  
  for (auto node : targetNodes) {
    auto newZOrder = node->getLocalZOrder() + OVERLAY_Z_ORDER;
    node->setLocalZOrder(newZOrder);
  }
  
  this->addChild(overlayLayer, OVERLAY_Z_ORDER - 1);
  
  auto fadeIn = FadeTo::create(OVERLAY_DURATION, OVERLAY_OPACITY);
  overlayLayer->runAction(fadeIn);
}

void GameplayLayer::_removeOverlay() {
  auto overlayLayer = this->getChildByName(OVERLAY_LAYER_NAME);
  
  auto fadeOut = FadeOut::create(OVERLAY_DURATION);
  auto changeLayer = CallFunc::create([=]() {
    for (auto node : this->getChildren()) {
      if (node->getLocalZOrder() > overlayLayer->getLocalZOrder()) {
        auto oldZOrder = node->getLocalZOrder() - OVERLAY_Z_ORDER;
        node->setLocalZOrder(oldZOrder);
      }
    }
  });
  auto removeSelf = RemoveSelf::create();
  
  overlayLayer->runAction(Sequence::create(fadeOut, changeLayer, removeSelf, NULL));
}

#pragma mark - UI Event Handlers

void GameplayLayer::_handleEndTurnTouched(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_END_PLAYER_TURN, this);
  }
}

#pragma mark - Event Handlers

void GameplayLayer::_handleActionDiceDragStarted(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  auto dice = sprite->getDice();
  
  sprite->setLocalZOrder(sprite->getLocalZOrder() + DRAG_Z_ORDER_DELTA);
  sprite->getDice()->setDocked(false);
  sprite->runAction(ScaleTo::create(0.2, 0.58));
  
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  if (DiceUtil::isMagicDice(dice)) {
    for (auto node : this->getChildren()) {
      if (IS(node, ActionDiceSprite) && node != sprite) {
        targetNodes.pushBack(node);
      }
    }
  } else {
    log("dragging other dice");
    
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    targetNodes.pushBack(dockableNodes);
    targetNodes.pushBack(dockableContainer);
    
    for (auto node : dockableNodes) {
      if (node->getChildren().size() > 0 &&
          node->getBoundingBox().containsPoint(dockableLocation)) {
        sprite->undock(this);
        break;
      }
    }
  }
  
  this->_addOverlay(targetNodes);
}

void GameplayLayer::_handleActionDiceDragMoved(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  auto dice = sprite->getDice();
  
  auto touchLocation = this->convertTouchToNodeSpace(touch);
  sprite->setPosition(touchLocation);
  
  if (DiceUtil::isMagicDice(dice)) {
    for (auto node : this->getChildren()) {
      if (IS(node, ActionDiceSprite) && node != sprite) {
        auto color = Color3B::WHITE;
        auto rect = node->getBoundingBox();
        
        if (rect.containsPoint(touch->getLocation())) {
          color = OK_COLOR;
        }
        
        node->setColor(color);
      }
    }
  } else {
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    for (auto node : dockableNodes) {
      auto color = Color3B::WHITE;
      auto rect = node->getBoundingBox();
      
      rect.origin -= Vec2(DOCKABLE_HIDDEN_MARGIN, 0);
      rect.size = rect.size + Size(DOCKABLE_HIDDEN_MARGIN * 2, 0);
      
      if (node->getChildren().size() == 0 &&
          rect.containsPoint(dockableLocation)) {
        color = OK_COLOR;
      }
      
      node->setColor(color);
    }
  }
}

void GameplayLayer::_handleActionDiceDragEnded(EventCustom* event) {
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  auto dice = sprite->getDice();
  
  sprite->setLocalZOrder(sprite->getLocalZOrder() - DRAG_Z_ORDER_DELTA);
  
  this->_removeOverlay();
  
  bool moved = false;
  auto position = Vec2::ZERO;
  
  if (DiceUtil::isMagicDice(dice)) {
    for (auto node : this->getChildren()) {
      if (IS(node, ActionDiceSprite) && node != sprite) {
        auto targetDice = ((ActionDiceSprite*) node)->getDice();
        auto rect = node->getBoundingBox();
        
        if (rect.containsPoint(touch->getLocation())) {
          node->setColor(Color3B::WHITE);
          this->_triggerMagicDiceOnTargetDice(targetDice);
          break;
        }
      }
    }
  } else {
    auto dockableContainer = this->_getDockableContainer();
    auto dockableNodes = dockableContainer->getDockableNodes();
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    for (auto node : dockableNodes) {
      auto rect = node->getBoundingBox();
      
      rect.origin -= Vec2(DOCKABLE_HIDDEN_MARGIN, 0);
      rect.size = rect.size + Size(DOCKABLE_HIDDEN_MARGIN * 2, 0);
      
      if (node->getChildren().size() == 0 &&
          rect.containsPoint(dockableLocation)) {
        moved = true;
        node->setColor(Color3B::WHITE);
        
        sprite->dockOnNode(node);
        
        position = PositionUtil::centerOfNode(node);
        
        break;
      }
    }
  }
  
  if (moved) {
    auto move = MoveTo::create(0.1, position);
    sprite->runAction(move);
    sprite->getDice()->setDocked(true);
    
    log("animate move");
  } else {
    auto move = MoveTo::create(0.2, sprite->getOriginalPosition());
    auto scale = ScaleTo::create(0.2, 1);
    
    sprite->runAction(Spawn::create(move, scale, NULL));
    log("animate back");
  }
}