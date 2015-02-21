//
//  BackMenu.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "BackMenu.h"
#include "BackLabel.h"

USING_NS_CC;

Menu* BackMenu::createMenu() {
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  
  auto backLabel = BackLabel::create();
  auto menuItem = MenuItemLabel::create(backLabel, [&](Ref *sender) {
    Director::getInstance()->popScene();
  });
  auto backMenu = Menu::createWithItem(menuItem);
  
  float margin = visibleSize.width / 10;
  
  float x = visibleSize.width - backLabel->getContentSize().width / 2 -  margin;
  float y = visibleOrigin.y + margin;
  
  backMenu->setPosition(Vec2(x, y));
  
  return backMenu;
}