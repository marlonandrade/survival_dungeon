//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "BackgroundLayer.h"

USING_NS_CC;

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->adjustInitialLayers();
  
  return true;
}

void GameplayScene::adjustInitialLayers() {
  this->addChild(BackgroundLayer::create());
}