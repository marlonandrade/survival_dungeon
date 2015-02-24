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

#define DUNGEON_LAYER_TAG     1000
#define GAMEOBJECTS_LAYER_TAG 1001
#define CONTROLS_LAYER_TAG    1002

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->setGame(Game::create());
  this->adjustInitialLayers();
  
  return true;
}

#pragma mark - Private Interface

void GameplayScene::adjustInitialLayers() {
  this->addChild(BackgroundLayer::create(), -2);
  this->addChild(this->_createDungeonLayer(), -1);
  this->addChild(this->_createGameObjectsLayer(), 0);
  this->addChild(this->_createControlsLayer(), 1);
}

Layer* GameplayScene::_createDungeonLayer() {
  auto dungeonLayer = Layer::create();
  dungeonLayer->setTag(DUNGEON_LAYER_TAG);
  
  auto dungeon = this->getGame()->getDungeon();
  auto initialRoom = dungeon->getInitialRoom();
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  Vec2 center = Vec2(visibleSize.width / 2 + visibleOrigin.x,
                     visibleSize.height / 2 + visibleOrigin.y);
  
  initialSprite->setPosition(center);
  
  dungeonLayer->addChild(initialSprite);
  
  return dungeonLayer;
}

Layer* GameplayScene::_createGameObjectsLayer() {
  auto gameObjectsLayer = Layer::create();
  gameObjectsLayer->setTag(GAMEOBJECTS_LAYER_TAG);
  
  return gameObjectsLayer;
}

Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setTag(CONTROLS_LAYER_TAG);
  
  return controlsLayer;
}

Layer* GameplayScene::getDungeonLayer() {
  return (Layer*) this->getChildByTag(DUNGEON_LAYER_TAG);
}

Layer* GameplayScene::getGameObjectsLayer() {
  return (Layer*) this->getChildByTag(GAMEOBJECTS_LAYER_TAG);
}

Layer* GameplayScene::getControlsLayer() {
  return (Layer*) this->getChildByTag(CONTROLS_LAYER_TAG);
}