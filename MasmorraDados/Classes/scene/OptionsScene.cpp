//
//  OptionsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "OptionsScene.h"

USING_NS_CC;

Scene* OptionsScene::createScene() {
  auto scene = Scene::create();
  auto layer = OptionsScene::create();
  scene->addChild(layer);
  return scene;
}

bool OptionsScene::init() {
  if (!InnerMenuLayer::init("Opcoes")) {
    return false;
  }
  
  return true;
}