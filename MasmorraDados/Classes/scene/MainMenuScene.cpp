//
//  MainMenuScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "MainMenuScene.h"

#include "Definitions.h"

#include "CreditsScene.h"
#include "OptionsScene.h"
#include "NewGameScene.h"
#include "RulesScene.h"

#include "ActionDice.h"
#include "Dice.h"
#include "DiceFace.h"
#include "Game.h"
#include "GameOptions.h"
#include "MajorMonsterDice.h"
#include "MinorMonsterDice.h"

USING_NS_CC;

#pragma mark - Private Interface

Menu* MainMenuScene::createMenu() {
  Vector<MenuItem*> menuItems;
  
  Size visibleSize = Director::getInstance()->getVisibleSize();
  float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
  
  TTFConfig labelConfig;
  labelConfig.fontFilePath = "fonts/farcry.ttf";
  labelConfig.fontSize = 32 * scaleFactor;
  
  auto iniciarLabel = Label::createWithTTF(labelConfig, "INICIAR");
  auto iniciarMenuItem = MenuItemLabel::create(iniciarLabel, [&](Ref* sender) {
    auto newGameScene = NewGameScene::createScene();
    Director::getInstance()->pushScene(newGameScene);
  });
  menuItems.pushBack(iniciarMenuItem);
  
  auto rulesLabel = Label::createWithTTF(labelConfig, "REGRAS");
  auto rulesMenuItem = MenuItemLabel::create(rulesLabel, [&](Ref* sender) {
    auto rulesScene = RulesScene::createScene();
    Director::getInstance()->pushScene(rulesScene);
  });
  menuItems.pushBack(rulesMenuItem);
  
  auto optionsLabel = Label::createWithTTF(labelConfig, "OPCOES");
  auto optionsMenuItem = MenuItemLabel::create(optionsLabel, [&](Ref* sender) {
    auto optionsScene = OptionsScene::createScene();
    Director::getInstance()->pushScene(optionsScene);
  });
  menuItems.pushBack(optionsMenuItem);
  
  auto creditsLabel = Label::createWithTTF(labelConfig, "CREDITOS");
  auto creditsMenuItem = MenuItemLabel::create(creditsLabel, [&](Ref* sender) {
    auto creditsScene = CreditsScene::createScene();
    Director::getInstance()->pushScene(creditsScene);
  });
  menuItems.pushBack(creditsMenuItem);
  
  float margin = visibleSize.height / 8;
  ssize_t size = menuItems.size();
  for (int i = 0; i < size; i++) {
    auto menuItem = menuItems.at(i);
    menuItem->setPositionY(margin/2 + ((size - i - 3) * margin));
  }
  
  return Menu::createWithArray(menuItems);
}

LayerColor* MainMenuScene::getConfirmQuitLayer() {
  if (!_confirmQuitLayer) {
    _confirmQuitLayer = LayerColor::create(Color4B(0, 0, 0, 200));
    CC_SAFE_RETAIN(_confirmQuitLayer);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
    
    float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
    float centerX = visibleSize.width / 2 + visibleOrigin.x;
    float centerY = visibleSize.height / 2 + visibleOrigin.y;
    
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/farcry.ttf";
    labelConfig.fontSize = 45 * scaleFactor;
    
    auto questionLabel = Label::createWithTTF(labelConfig, "DESEJA REALMENTE SAIR?");
    
    labelConfig.fontSize = 38 * scaleFactor;
    
    Vector<MenuItem*> menuItems;
    auto yesLabel = Label::createWithTTF(labelConfig, "SIM");
    auto yesMenuItem = MenuItemLabel::create(yesLabel, [](Ref* sender) {
      Director::getInstance()->end();
    });
    yesMenuItem->setPosition(Vec2(-80 * scaleFactor, 0));
    
    auto noLabel = Label::createWithTTF(labelConfig, "NAO");
    auto noMenuItem = MenuItemLabel::create(noLabel, [&](Ref *sender) {
      _confirmQuitLayer->removeFromParent();
    });
    noMenuItem->setPosition(Vec2(80 * scaleFactor, 0));
    
    menuItems.pushBack(yesMenuItem);
    menuItems.pushBack(noMenuItem);
    
    auto menu = Menu::createWithArray(menuItems);
    
    questionLabel->setPosition(Vec2(centerX, centerY + 50 * scaleFactor));
    menu->setPosition(Vec2(centerX, centerY - 50 * scaleFactor));
    
    _confirmQuitLayer->addChild(questionLabel);
    _confirmQuitLayer->addChild(menu);
  }
  
  return _confirmQuitLayer;
}

#pragma mark - Public Interface

Scene* MainMenuScene::createScene() {
  auto scene = Scene::create();
  auto layer = MainMenuScene::create();
  scene->addChild(layer);
  return scene;
}

bool MainMenuScene::init() {
  if (!BaseMenuLayer::init("Menu Inicial")) {
    return false;
  }
  
  auto director = Director::getInstance();
  
  Size visibleSize = director->getVisibleSize();
  Vec2 visibleOrigin = director->getVisibleOrigin();
  
  float centerX = visibleOrigin.x + visibleSize.width / 2;
  float centerY = visibleOrigin.y + visibleSize.height / 2;
  
  auto menu = this->createMenu();
  menu->setPosition(Vec2(centerX, centerY));
  
  this->addChild(menu);
  
  return true;
}

void MainMenuScene::leave() {
  if (!getConfirmQuitLayer()->getParent()) {
    this->addChild(getConfirmQuitLayer());
  }
}