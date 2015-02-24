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

#define DUNGEON_LAYER_TAG 1000

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
  this->addChild(BackgroundLayer::create(), -1);
  
  auto dungeonLayer = Layer::create();
  dungeonLayer->setTag(DUNGEON_LAYER_TAG);
  this->addChild(dungeonLayer);
  // dungeon layer
  // overlay/controls layer
  
  auto dungeon = this->getGame()->getDungeon();
  auto initialRoom = dungeon->getInitialRoom();
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  Vec2 center = Vec2(visibleSize.width / 2 + visibleOrigin.x,
                     visibleSize.height / 2 + visibleOrigin.y);
  
  initialSprite->setPosition(center);
  
  this->getDungeonLayer()->addChild(initialSprite);
}

Layer* GameplayScene::getDungeonLayer() {
  return (Layer*) this->getChildByTag(DUNGEON_LAYER_TAG);
}