//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

USING_NS_CC;

Scene* GameplayScene::createScene() {
  auto scene = Scene::create();
  auto layer = GameplayScene::create();
  scene->addChild(layer);
  return scene;
}

bool GameplayScene::init() {
  if (!Layer::init()) {
    return false;
  }
  
  return true;
}