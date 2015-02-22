//
//  InnerMenuLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "InnerMenuLayer.h"
#include "Definitions.h"
#include "BackMenu.h"

USING_NS_CC;

bool InnerMenuLayer::init(std::string title) {
  if (!BaseMenuLayer::init(title)) {
    return false;
  }
  
  this->addChild(BackMenu::createMenu());
  
  return true;
}

#pragma mark - Exit Layer Methods

void InnerMenuLayer::leave() {
  Director::getInstance()->popScene();
}
