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
#include "RoomPlacement.h"

USING_NS_CC;

#define DUNGEON_LAYER_TAG     1000
#define CONTROLS_LAYER_TAG    1001

#define CHARACTER_SPRITE_TAG  2000

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  auto game = Game::createWithRoomPlacedDelegate([&](Vector<RoomPlacement*> placements) {
    float delayTime = 0;
    int zOrder = placements.size();
    
    for (auto placement : placements) {
      auto room = placement->getRoom();
      auto position = placement->getPosition();
      
      auto roomSprite = Sprite::create(room->getImagePath());
      
      auto size = Director::getInstance()->getVisibleSize();
      auto origin = Director::getInstance()->getVisibleOrigin();
      
      roomSprite->setPosition(Vec2(origin.x + size.width / 2 - TILE_DIMENSION / 2 - 20,
                                   origin.y + size.height / 2 - TILE_DIMENSION / 2 - 20));
      
      this->getDungeonLayer()->addChild(roomSprite, zOrder);
      
      auto centerPosition = INITIAL_POSITION;
      
      auto offsetX = position.x - centerPosition.x;
      auto offsetY = position.y - centerPosition.y;
      
      auto spritePosition = Vec2(offsetX * TILE_DIMENSION,
                                 offsetY * TILE_DIMENSION);
      
      auto delay = DelayTime::create(delayTime);
      auto topZOrder = CallFunc::create([=]() {
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + 10);
      });
      auto easeMove = EaseBackIn::create(MoveTo::create(PLACE_ROOM_DURATION, spritePosition));
      auto normalizeZOrder = CallFunc::create([=]() {
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
      });
      
      roomSprite->runAction(Sequence::create(delay, topZOrder, easeMove, normalizeZOrder, NULL));
      
      delayTime += PLACE_ROOM_DURATION;
      zOrder--;
    }
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
  dungeonLayer->addChild(initialSprite, DUNGEON_ROOM_Z_ORDER);
  
  auto characterSprite = CharacterSprite::create();
  characterSprite->setTag(CHARACTER_SPRITE_TAG);
  dungeonLayer->addChild(characterSprite, GAME_OBJECTS_Z_ORDER);
  
  return dungeonLayer;
}


Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setTag(CONTROLS_LAYER_TAG);
  
  return controlsLayer;
}

Layer* GameplayScene::getDungeonLayer() {
  return (Layer*) this->getChildByTag(DUNGEON_LAYER_TAG);
}

Layer* GameplayScene::getControlsLayer() {
  return (Layer*) this->getChildByTag(CONTROLS_LAYER_TAG);
}

void GameplayScene::_adjustCharacterSpritePosition() {
  auto sprite = this->getDungeonLayer()->getChildByTag(CHARACTER_SPRITE_TAG);
  
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
