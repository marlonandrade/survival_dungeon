//
//  BaseMenuLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "BaseMenuLayer.h"
#include "Definitions.h"

USING_NS_CC;

bool BaseMenu::init(std::string title) {
  if (!Exit::init()) {
    return false;
  }
  
  Director *director = Director::getInstance();
  
  Size visibleSize = director->getVisibleSize();
  Vec2 visibleOrigin = director->getVisibleOrigin();
  
  float centerX = visibleOrigin.x + visibleSize.width / 2;
  float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
  float fontSize = 50 * scaleFactor;
  
  std::transform(title.begin(), title.end(), title.begin(), ::toupper);
  
  auto label = Label::createWithTTF(title, "fonts/farcry.ttf", fontSize);
  label->setPosition(Vec2(centerX,
                          visibleOrigin.y + visibleSize.height - 80));
  
  this->addChild(label);
  
  return true;
}

#pragma mark - Exit Layer Methods

void BaseMenu::leave() {
  Director::getInstance()->end();
}