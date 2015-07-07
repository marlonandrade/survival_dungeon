//
//  IntroScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "IntroScene.h"

#include "Images.h"
#include "Game.h"
#include "GameplayScene.h"

USING_NS_CC;

bool IntroScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
//  srand(std::time(0));
  srand(0);
  
  auto layer = Layer::create();
  
  auto director = Director::getInstance();
  
  Size visibleSize = director->getVisibleSize();
  Vec2 visibleOrigin = director->getVisibleOrigin();
  
  Vec2 center = Vec2(visibleSize.width / 2 + visibleOrigin.x,
                     visibleSize.height / 2 + visibleOrigin.y);
  
  auto introImage = Sprite::create(IMG_INTRO);
  
  float scaleX = visibleSize.width / introImage->getContentSize().width;
  float scaleY = visibleSize.height / introImage->getContentSize().height;
  
  introImage->setPosition(center);
  introImage->setScale(scaleX, scaleY);
  
  layer->addChild(introImage);
  
  this->addChild(layer);
  
  this->schedule(schedule_selector(IntroScene::loadResources));
  
  return true;
}

void IntroScene::loadResources(float deltaTime) {
  auto gameplayScene = GameplayScene::create();
  Director::getInstance()->replaceScene(gameplayScene);
}
