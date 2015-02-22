//
//  RulesScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "RulesScene.h"

USING_NS_CC;

Scene* RulesScene::createScene() {
  auto scene = Scene::create();
  auto layer = RulesScene::create();
  scene->addChild(layer);
  return scene;
}

bool RulesScene::init() {
  if (!InnerMenuLayer::init("Regras")) {
  return false;
  }
  
  return true;
}