//
//  NewGameScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "NewGameScene.h"

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
  
  auto director = Director::getInstance();
  
  Size visibleSize = director->getVisibleSize();
  Vec2 visibleOrigin = director->getVisibleOrigin();
  
  float x = 200;
  float y = visibleOrigin.y + visibleSize.height / 2;
  
  auto chars = FileUtils::getInstance()->getValueMapFromFile("res/characters.plist");
  
  auto baseChars = chars.at("base").asValueMap();
  for (auto baseChar : baseChars) {
    auto key = std::get<0>(baseChar);
    auto properties = std::get<1>(baseChar).asValueMap();
    
    log("%s", key.c_str());
    auto sprite = Sprite::create(properties.at("image").asString());
    sprite->setPosition(Vec2(x, y));
    
    this->addChild(sprite);
    
    x += sprite->getContentSize().width + 100;
  }
  
  return true;
}