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
  
  float marginX = visibleSize.width / 10;
  float marginY = visibleSize.height / 10;
  
  float x = visibleOrigin.x + marginX;
  float y = visibleOrigin.y + marginY;
  
  backMenu->setPosition(Vec2(x, y));
  
  return backMenu;
}