//
//  DockableContainer.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "DockableContainer.h"

#include "Images.h"
#include "NodeNames.h"

#include "ActionDiceSprite.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DockableContainer::init() {
  if (!Node::init()) {
    return false;
  }
  
  this->setName(DOCK_CONTAINER_NODE_NAME);
  
  this->_setupChildren();
  
  return true;
}

void DockableContainer::resetDockableNodes() {
  for (auto dockableNode : this->getDockableNodes()) {
    if (dockableNode->getChildren().size()) {
      auto sprite = (ActionDiceSprite*) dockableNode->getChildren().at(0);
      sprite->undock((Layer*) this->getParent());
    }
    
    dockableNode->setColor(Color3B::WHITE);
  }
}

Vector<Node*> DockableContainer::getDockableNodes() {
  return this->getChildren();
}

#pragma mark - Private Interface

void DockableContainer::_setupChildren() {
  int dockableSpaces = 6;
  
  auto height = 0;
  auto width = 0;
  auto marginBetweenSpaces = 1;
  
  for (int i = 0; i < dockableSpaces; i++) {
    auto sprite = Sprite::create(IMG_DICE_ACTION_DOCK);
    
    width = sprite->getContentSize().width;
    height = sprite->getContentSize().height;
    
    auto x = 0.f;
    auto y = height * i + ((i + 1) * marginBetweenSpaces);
    
    sprite->setPosition(Vec2(x, y));
    
    this->addChild(sprite);
  }
  
  auto totalWidth = width;
  auto totalHeight = height * dockableSpaces + marginBetweenSpaces * (dockableSpaces + 1);
  
  this->setContentSize(Size(totalWidth, totalHeight));
}
