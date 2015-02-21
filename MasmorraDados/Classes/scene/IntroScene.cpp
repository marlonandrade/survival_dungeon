//
//  IntroScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "IntroScene.h"

#include "GameResources.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* IntroScene::createScene() {
  auto scene = Scene::create();
  auto layer = IntroScene::create();
  scene->addChild(layer);
  return scene;
}

bool IntroScene::init() {
  if (!Layer::init()) {
    return false;
  }
  
  auto director = Director::getInstance();
  
  Size visibleSize = director->getVisibleSize();
  Vec2 visibleOrigin = director->getVisibleOrigin();
  
  Vec2 center = Vec2(visibleSize.width / 2 + visibleOrigin.x,
                     visibleSize.height / 2 + visibleOrigin.y);
  
  auto introImage = Sprite::create("images/intro.jpg");
  
  float scaleX = visibleSize.width / introImage->getContentSize().width;
  float scaleY = visibleSize.height / introImage->getContentSize().height;
  
  introImage->setPosition(center);
  introImage->setScale(scaleX, scaleY);
  
  this->addChild(introImage, 0);
  
  this->schedule(schedule_selector(IntroScene::loadResources));
  
  return true;
}

void IntroScene::loadResources(float deltaTime) {
  GameResources::getInstance().loadResources();
  
  auto mainMenuScene = MainMenuScene::createScene();
  Director::getInstance()->replaceScene(mainMenuScene);
}
