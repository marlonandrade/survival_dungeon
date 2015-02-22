//
//  CreditsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "CreditsScene.h"

USING_NS_CC;

Scene* CreditsScene::createScene() {
  auto scene = Scene::create();
  auto layer = CreditsScene::create();
  scene->addChild(layer);
  return scene;
}

bool CreditsScene::init() {
  if (!InnerMenuLayer::init("Creditos")) {
    return false;
  }
  
  return true;
}