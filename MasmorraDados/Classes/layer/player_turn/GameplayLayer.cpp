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

#include "ActionDiceDragData.h"

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
  
  this->_setupFreeBootSymbol();
  this->_setupDockableDice();
  this->_setupFinalizarButton();
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
  auto freeBootSprite = this->getChildByName(FREE_BOOT_SPRITE_NAME);
  freeBootSprite->removeAllChildren();
}

void GameplayLayer::resetDockableNodes() {
  for (auto dockableNode : this->getDockableNodes()) {
    if (dockableNode->getChildren().size()) {
      auto sprite = (ActionDiceSprite*) dockableNode->getChildren().at(0);
      sprite->undock(this);
    }
    
    dockableNode->setColor(Color3B::WHITE);
  }
}

Vector<Node*> GameplayLayer::getDockableNodes() {
  return this->_getDockContainer()->getChildren();
}

#pragma mark - Private Interface

void GameplayLayer::_setupFreeBootSymbol() {
  auto sprite = Sprite::create(IMG_DICE_ACTION_FREE_BOOT);
  sprite->setName(FREE_BOOT_SPRITE_NAME);
  
  auto size = sprite->getContentSize() / 2;
  auto x = DOCK_MARGIN + size.width;
  auto y = this->getContentSize().height - (DOCK_MARGIN + size.height);
  
  sprite->setPosition(Vec2(x, y));
  
  this->addChild(sprite);
}

void GameplayLayer::_setupDockableDice() {
  auto dockContainer = Node::create();
  dockContainer->setName(DOCK_CONTAINER_NODE_NAME);
  
  auto bootSprite = this->getChildByName(FREE_BOOT_SPRITE_NAME);
  
  this->addChild(dockContainer);
  
  int dockableSpaces = 6;
  
  auto height = 0;
  auto width = 0;
  auto marginBetweenSpaces = 1;
  
  for (int i = 0; i < dockableSpaces; i++) {
    auto sprite = Sprite::create(IMG_DICE_ACTION_DOCK);
    
    width = sprite->getContentSize().width;
    height = sprite->getContentSize().height;
    
    auto x = 0.f;
    auto y = height * i + (i * marginBetweenSpaces);
    
    sprite->setPosition(Vec2(x, y));
    
    dockContainer->addChild(sprite);
  }
  
  auto bootSize = bootSprite->getContentSize();
  
  auto dockX = DOCK_MARGIN + bootSize.width / 2;
  auto dockY = this->getContentSize().height -
      (DOCK_MARGIN + (dockableSpaces - 0.5) * height +
       bootSize.height + dockableSpaces * marginBetweenSpaces);
  
  auto totalWidth = width;
  auto totalHeight = height * dockableSpaces + (dockableSpaces - 1) * marginBetweenSpaces;
  
  dockContainer->setPosition(Vec2(dockX, dockY));
  dockContainer->setContentSize(Size(totalWidth, totalHeight));
}

void GameplayLayer::_setupFinalizarButton() {
  auto button = ui::Button::create(IMG_BUTTON_END_TURN_NORMAL,
                                   IMG_BUTTON_END_TURN_SELECTED,
                                   IMG_BUTTON_END_TURN_DISABLED);
  button->setName(END_TURN_BUTTON_NAME);
  button->addTouchEventListener(CC_CALLBACK_2(GameplayLayer::_handleEndTurnTouched, this));
  
  auto size = button->getContentSize() / 2;
  auto x = this->getContentSize().width - (END_TURN_MARGIN + size.width);
  auto y = this->getContentSize().height - (END_TURN_MARGIN + size.height);
  
  button->setPosition(Vec2(x, y));
  
  this->addChild(button);
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
  
  auto freeBootSpentCallback = CC_CALLBACK_1(GameplayLayer::_handleActionFreeBootSpent, this);
  this->setFreeBootSpentListener(
    dispatcher->addCustomEventListener(EVT_ACTION_FREE_BOOT_SPENT, freeBootSpentCallback)
  );
}

Node* GameplayLayer::_getDockContainer() {
  return this->getChildByName(DOCK_CONTAINER_NODE_NAME);
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
  log("drag started");
  
  auto data = (ActionDiceDragData*) event->getUserData();
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  auto dice = sprite->getDice();
  
  sprite->setLocalZOrder(sprite->getLocalZOrder() + DRAG_Z_ORDER_DELTA);
  sprite->getDice()->setDocked(false);
  sprite->runAction(ScaleTo::create(0.2, 0.58));
  
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  if (dice->getSelectedFace()->getImagePath() == IMG_DICE_ACTION_MAGIC) {
    log("dragging magic");
    for (auto node : this->getChildren()) {
      if (IS(node, ActionDiceSprite) && node != sprite) {
        log("dice");
        targetNodes.pushBack(node);
      }
    }
  } else {
    log("dragging other dice");
    
    auto dockableNodes = this->getDockableNodes();
    auto dockableContainer = this->getChildByName(DOCK_CONTAINER_NODE_NAME);
    
    targetNodes.pushBack(dockableNodes);
    targetNodes.pushBack(dockableContainer);
    
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    for (auto node : this->getDockableNodes()) {
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
  
  if (dice->getSelectedFace()->getImagePath() == IMG_DICE_ACTION_MAGIC) {
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
    auto dockableContainer = this->getChildByName(DOCK_CONTAINER_NODE_NAME);
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    for (auto node : this->getDockableNodes()) {
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
  
  if (dice->getSelectedFace()->getImagePath() == IMG_DICE_ACTION_MAGIC) {
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
    auto dockableContainer = this->getChildByName(DOCK_CONTAINER_NODE_NAME);
    auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(touch);
    
    for (auto node : this->getDockableNodes()) {
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

void GameplayLayer::_handleActionFreeBootSpent(EventCustom* event) {
  auto freeBootSprite = this->getChildByName(FREE_BOOT_SPRITE_NAME);
  auto spentActionSprite = Sprite::create(IMG_DICE_ACTION_SPENT);
  spentActionSprite->setPosition(Vec2(freeBootSprite->getContentSize().width / 2,
                                      freeBootSprite->getContentSize().height / 2));
  freeBootSprite->addChild(spentActionSprite);
}