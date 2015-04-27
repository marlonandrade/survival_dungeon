//
//  PlayerSkillsLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#include "PlayerSkillsLayer.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

bool PlayerSkillsLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->_setupFreeBootSymbol();
  this->_setupDockableDice();
  
  return true;
}

Vector<Node*> PlayerSkillsLayer::getDockableNodes() {
  return this->_getDockContainer()->getChildren();
}

#pragma mark - Private Interface

void PlayerSkillsLayer::_setupFreeBootSymbol() {
  auto sprite = Sprite::create(IMG_DICE_ACTION_FREE_BOOT);
  sprite->setName(FREE_BOOT_SPRITE_NAME);
  
  auto size = sprite->getContentSize() / 2;
  auto x = DOCK_MARGIN + size.width;
  auto y = this->getContentSize().height - (DOCK_MARGIN + size.height);
  
  sprite->setPosition(Vec2(x, y));
  
  this->addChild(sprite);
}

void PlayerSkillsLayer::_setupDockableDice() {
  auto dockContainer = Node::create();
  dockContainer->setName(DOCK_CONTAINER_NODE_NAME);
  
  auto bootSprite = this->getChildByName(FREE_BOOT_SPRITE_NAME);
  
  this->addChild(dockContainer);
  
  int dockableSpaces = 6;
  
  auto height = 0;
  auto marginBetweenSpaces = 1;
  
  for (int i = 0; i < dockableSpaces; i++) {
    auto sprite = Sprite::create(IMG_DICE_ACTION_DOCK);
    
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
  
  dockContainer->setPosition(Vec2(dockX, dockY));
}

Node* PlayerSkillsLayer::_getDockContainer() {
  return this->getChildByName(DOCK_CONTAINER_NODE_NAME);
}