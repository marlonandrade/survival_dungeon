//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "BackgroundLayer.h"
#include "CharacterSprite.h"

USING_NS_CC;

#define DUNGEON_LAYER_TAG     1000
#define GAMEOBJECTS_LAYER_TAG 1001
#define CONTROLS_LAYER_TAG    1002

#define CHARACTER_SPRITE_TAG  2000

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  float delayTime = 0;
  
  auto game = Game::createWithRoomPlacedDelegate([&](Vec2 position, DungeonRoom* room) {
    auto roomSprite = Sprite::create(room->getImagePath());
    
    auto size = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    roomSprite->setPosition(Vec2(origin.x + size.width - DUNGEON_SIZE - 20,
                                 origin.y + size.height - DUNGEON_SIZE - 20));
    
    this->getDungeonLayer()->addChild(roomSprite);
    
    auto centerPosition = INITIAL_POSITION;
    
    auto offsetX = position.x - centerPosition.x;
    auto offsetY = position.y - centerPosition.y;
    
    auto spritePosition = Vec2(offsetX * TILE_DIMENSION,
                               offsetY * TILE_DIMENSION);
    
    auto delay = DelayTime::create(delayTime);
    auto move = MoveTo::create(0.3, spritePosition);
    
    roomSprite->runAction(Sequence::createWithTwoActions(delay, move));
    
    delayTime += 0.3;
    if (delayTime > 2) delayTime = 0;
  });
  
  this->setGame(game);
  this->adjustInitialLayers();
  
  return true;
}

#pragma mark - Private Interface

void GameplayScene::adjustInitialLayers() {
  auto center = this->_centerOfScene();
  
  auto backgroundLayer = BackgroundLayer::create();
  backgroundLayer->setPosition(center);
  this->addChild(backgroundLayer, -2);
  
  auto dungeonLayer = this->_createDungeonLayer();
  dungeonLayer->setPosition(center);
  this->addChild(dungeonLayer, -1);
  
  auto gameObjectsLayer = this->_createGameObjectsLayer();
  gameObjectsLayer->setPosition(center);
  this->addChild(gameObjectsLayer, 0);
  
  auto controlsLayer = this->_createControlsLayer();
  controlsLayer->setPosition(center);
  this->addChild(controlsLayer, 1);
  
  this->getGame()->setCharacterPosition(INITIAL_POSITION);
  this->_adjustCharacterSpritePosition();
}

Layer* GameplayScene::_createDungeonLayer() {
  auto dungeonLayer = Layer::create();
  dungeonLayer->setTag(DUNGEON_LAYER_TAG);
  
  auto dungeon = this->getGame()->getDungeon();
  auto initialRoom = dungeon->getInitialRoom();
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  dungeonLayer->addChild(initialSprite);
  
  return dungeonLayer;
}

Layer* GameplayScene::_createGameObjectsLayer() {
  auto gameObjectsLayer = Layer::create();
  gameObjectsLayer->setTag(GAMEOBJECTS_LAYER_TAG);
  
  auto characterSprite = CharacterSprite::create();
  characterSprite->setTag(CHARACTER_SPRITE_TAG);
  gameObjectsLayer->addChild(characterSprite);
  
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

void GameplayScene::_adjustCharacterSpritePosition() {
  auto sprite = this->getGameObjectsLayer()->getChildByTag(CHARACTER_SPRITE_TAG);
  
  auto characterPosition = this->getGame()->getCharacterPosition();
  
  int xOffset = characterPosition.x - (DUNGEON_SIZE / 2);
  int yOffset = characterPosition.y - (DUNGEON_SIZE / 2);
  
  auto center = this->_centerOfScene();
  auto position = Vec2(xOffset * TILE_DIMENSION,
                       yOffset * TILE_DIMENSION);
  
  sprite->setPosition(position);
}

Vec2 GameplayScene::_centerOfScene() {
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  return Vec2(visibleSize.width / 2 + visibleOrigin.x,
              visibleSize.height / 2 + visibleOrigin.y);
}
