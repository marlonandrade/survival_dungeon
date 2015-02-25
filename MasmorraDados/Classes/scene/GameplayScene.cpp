//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "BackgroundLayer.h"
#include "CharacterDiceSprite.h"
#include "RoomPlacement.h"

USING_NS_CC;

#define OBJECTS_LAYER_TAG     1000
#define CONTROLS_LAYER_TAG    1001

#define CHARACTER_DICE_SPRITE_TAG  2000

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
      
      auto deckPosition = Vec2(origin.x + size.width - TILE_DIMENSION / 2 - 20,
                               origin.y + size.height - TILE_DIMENSION / 2 - 20);
      roomSprite->setPosition(deckPosition);
      
      this->getObjectsLayer()->addChild(roomSprite, zOrder);
      
      auto spritePosition = this->_positionInScene(position);
      
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
  this->addChild(backgroundLayer, -2);
  
  auto objectsLayer = this->_createObjectsLayer();
  this->addChild(objectsLayer, -1);
  
  auto controlsLayer = this->_createControlsLayer();
  this->addChild(controlsLayer, 1);
  
  this->getGame()->setCharacterPosition(INITIAL_POSITION);
  this->_adjustCharacterDiceSpritePosition();
}

Layer* GameplayScene::_createObjectsLayer() {
  auto objectsLayer = Layer::create();
  objectsLayer->setTag(OBJECTS_LAYER_TAG);
  
  auto initialRoom = this->getGame()->getDungeon()->getInitialRoom();
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  initialSprite->setPosition(this->_positionInScene(INITIAL_POSITION));
  objectsLayer->addChild(initialSprite, DUNGEON_ROOM_Z_ORDER);
  
  auto characterSprite = CharacterDiceSprite::create();
  characterSprite->setTag(CHARACTER_DICE_SPRITE_TAG);
  objectsLayer->addChild(characterSprite, GAME_OBJECTS_Z_ORDER);
  
  return objectsLayer;
}

Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setTag(CONTROLS_LAYER_TAG);
  
  return controlsLayer;
}

Layer* GameplayScene::getObjectsLayer() {
  return (Layer*) this->getChildByTag(OBJECTS_LAYER_TAG);
}

Layer* GameplayScene::getControlsLayer() {
  return (Layer*) this->getChildByTag(CONTROLS_LAYER_TAG);
}

Vec2 GameplayScene::_positionInScene(Vec2 gameCoordinate) {
  auto centerPosition = INITIAL_POSITION;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = gameCoordinate.x - centerPosition.x;
  auto offsetY = gameCoordinate.y - centerPosition.y;
  
  return Vec2(centerOfScene.x + offsetX * TILE_DIMENSION,
              centerOfScene.y + offsetY * TILE_DIMENSION);
}

void GameplayScene::_adjustCharacterDiceSpritePosition() {
  auto sprite = this->getObjectsLayer()->getChildByTag(CHARACTER_DICE_SPRITE_TAG);
  auto characterPosition = this->getGame()->getCharacterPosition();
  sprite->setPosition(this->_positionInScene(characterPosition));
}

Vec2 GameplayScene::_centerOfScene() {
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  return Vec2(visibleSize.width / 2 + visibleOrigin.x,
              visibleSize.height / 2 + visibleOrigin.y);
}
