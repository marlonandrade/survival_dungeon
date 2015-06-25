//
//  HudLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/24/15.
//
//

#include "HudLayer.h"

#include "NodeNames.h"

USING_NS_CC;

#pragma mark - Public Interface

bool HudLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(HUD_LAYER_NAME);
  this->_setupChildren();
  
  return true;
}

void HudLayer::adjustLevel(int level) {
  std::stringstream ss;
  ss << "Andar ";
  ss << level;
  
  auto label = this->_getLevelLabel();
  label->setString(ss.str());
}

#pragma mark - Private Interface

void HudLayer::_setupChildren() {
  auto label = Label::createWithTTF("", "fonts/DOWNCOME.TTF", 15);
  label->setAnchorPoint(Vec2(0, 0.5));
  label->setName(HUD_LEVEL_LABEL_NAME);
  label->setPosition(Vec2(40, this->getContentSize().height - 12));
  this->addChild(label);
}

Label* HudLayer::_getLevelLabel() {
  return (Label*) this->getChildByName(HUD_LEVEL_LABEL_NAME);
}