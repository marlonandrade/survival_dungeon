//
//  NewGameScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "NewGameScene.h"

#include "Character.h"
#include "Definitions.h"
#include "GameplayScene.h"
#include "GameResources.h"

USING_NS_CC;

Scene* NewGameScene::createScene() {
  auto scene = Scene::create();
  auto layer = NewGameScene::create();
  scene->addChild(layer);
  return scene;
}

bool NewGameScene::init() {
  if (!InnerMenuLayer::init("NOVO JOGO")) {
    return false;
 }
  
  this->addChild(this->characterSelectLayer());
  this->addChild(this->iniciarMenu());
  
  return true;
}

#define FIRST_CHAR_TAG  0300
#define SECOND_CHAR_TAG 0301

Layer* NewGameScene::characterSelectLayer() {
  Vector<MenuItem*> items;
  
  auto characterSelectPath = "images/character_select.png";
  
  auto firstChar = MenuItemImage::create(characterSelectPath, characterSelectPath, [&](Ref* sender) {
    MenuItemImage *firstSender = (MenuItemImage*) sender;
    
    auto firstChildren = firstSender->getChildByTag(FIRST_CHAR_TAG);
    if (!firstChildren) {
      float centerX = firstSender->getContentSize().width / 2;
      float centerY = firstSender->getContentSize().height / 2;
      
      auto alda = GameResources::getInstance().getCharacters().at("alda");
      
      auto aldaSprite = Sprite::create(alda->getImagePath());
      aldaSprite->setTag(FIRST_CHAR_TAG);
      aldaSprite->setPosition(Vec2(centerX, centerY));
      
      firstSender->addChild(aldaSprite);
    }
  });
  auto secondChar = MenuItemImage::create(characterSelectPath, characterSelectPath, [&](Ref* sender) {
    MenuItemImage *secondSender = (MenuItemImage*) sender;
    
    auto secondChildren = secondSender->getChildByTag(SECOND_CHAR_TAG);
    if (!secondChildren) {
      float centerX = secondSender->getContentSize().width / 2;
      float centerY = secondSender->getContentSize().height / 2;
      
      auto rufus = GameResources::getInstance().getCharacters().at("rufus");
      
      auto rufusSprite = Sprite::create(rufus->getImagePath());
      rufusSprite->setTag(SECOND_CHAR_TAG);
      rufusSprite->setPosition(Vec2(centerX, centerY));
      
      secondSender->addChild(rufusSprite);
    }
  });
  
  items.pushBack(firstChar);
  items.pushBack(secondChar);
  
  int spaceBetweenCards = 30;
  int halfCharacterCard = CHARACTER_CARD_WIDTH / 2;
  int position = halfCharacterCard + spaceBetweenCards / 2;
  
  firstChar->setPositionX(-position);
  secondChar->setPositionX(position);
  
  auto menu = Menu::createWithArray(items);
  
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  
  float centerX = visibleSize.width / 2 + visibleOrigin.x;
  float centerY = visibleSize.height / 2 + visibleOrigin.y;
  
  menu->setPosition(Vec2(centerX, centerY));
  
  return menu;
}


Menu* NewGameScene::iniciarMenu() {
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  
  float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
  
  TTFConfig labelConfig;
  labelConfig.fontFilePath = "fonts/farcry.ttf";
  labelConfig.fontSize = 30 * scaleFactor;
  
  auto jogarLabel = Label::createWithTTF(labelConfig, "JOGAR");
  auto menuItem = MenuItemLabel::create(jogarLabel, [&](Ref *sender) {
    auto gameScene = GameplayScene::createScene();
    Director::getInstance()->replaceScene(gameScene);
  });
  auto backMenu = Menu::createWithItem(menuItem);
  
  float marginX = visibleSize.width / 10;
  float marginY = visibleSize.height / 10;
  
  float x = visibleSize.width - jogarLabel->getContentSize().width / 2 - marginX;
  float y = visibleOrigin.y + marginY;
  
  backMenu->setPosition(Vec2(x, y));
  
  return backMenu;
}