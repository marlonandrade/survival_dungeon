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
#include "ScrollableLayer.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->_enableInteractions();
  
  auto game = Game::createWithRoomPlacedDelegate([&](Vector<RoomPlacement*> placements) {
    if (placements.size() > 0) {
      this->_disableInteractions();
    }
    
    float delayTime = 0;
    int zOrder = placements.size();
    
    for (auto placement : placements) {
      auto room = placement->getRoom();
      auto position = placement->getPosition();
      
      auto roomSprite = Sprite::create(room->getImagePath());
      auto name = this->getGame()->getDungeon()->nameForPosition(position);
      roomSprite->setName(name);
      
      auto size = Director::getInstance()->getVisibleSize();
      auto origin = Director::getInstance()->getVisibleOrigin();
      
      auto deckPosition = Vec2(origin.x + size.width - TILE_DIMENSION / 2 - 20,
                               origin.y + size.height - TILE_DIMENSION / 2 - 20);
      roomSprite->setPosition(deckPosition);
      
      this->_getObjectsLayer()->addChild(roomSprite, zOrder);
      
      auto spritePosition = this->_positionInScene(position);
      
      auto delay = DelayTime::create(delayTime);
      auto animationStarted = CallFunc::create([=]() {
        this->_disableInteractions();
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER + 10);
      });
      auto easeMove = EaseBackIn::create(MoveTo::create(PLACE_ROOM_DURATION, spritePosition));
      auto animationEnded = CallFunc::create([=]() {
        this->_enableInteractions();
        roomSprite->setLocalZOrder(DUNGEON_ROOM_Z_ORDER);
      });
      
      roomSprite->runAction(Sequence::create(delay, animationStarted, easeMove,
                                             animationEnded, NULL));
      
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
  
  auto scrollableLayer = ScrollableLayer::createWithDungeon(this->getGame()->getDungeon());
  
  scrollableLayer->addChild(BackgroundLayer::create(), -10);
  scrollableLayer->addChild(this->_createObjectsLayer(), 0);
  
  this->addChild(scrollableLayer, 0);
  this->addChild(this->_createControlsLayer(), 1);
  
  this->getGame()->setCharacterPosition(INITIAL_POSITION);
  this->_adjustCharacterDiceSpritePosition();
}

Layer* GameplayScene::_createObjectsLayer() {
  auto objectsLayer = Layer::create();
  objectsLayer->setTag(OBJECTS_LAYER_TAG);
  
  auto initialRoom = this->getGame()->getDungeon()->getInitialRoom();
  auto initialPosition = INITIAL_POSITION;
  
  auto initialSprite = Sprite::create(initialRoom->getImagePath());
  auto name = this->getGame()->getDungeon()->nameForPosition(initialPosition);
  initialSprite->setName(name);
  initialSprite->setPosition(this->_positionInScene(INITIAL_POSITION));
  objectsLayer->addChild(initialSprite, DUNGEON_ROOM_Z_ORDER);
  
  objectsLayer->addChild(this->_createCharacterDiceSprite(), GAME_OBJECTS_Z_ORDER);
    
  return objectsLayer;
}

Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setTag(CONTROLS_LAYER_TAG);
  
  return controlsLayer;
}

Node* GameplayScene::_createCharacterDiceSprite() {
  return CharacterDiceSprite::createWithDelegate(this);
}

Layer* GameplayScene::_getScrollableLayer() {
  return (Layer*) this->getChildByTag(SCROLLABLE_LAYER_TAG);
}

Layer* GameplayScene::_getObjectsLayer() {
  auto scrollableLayer = this->_getScrollableLayer();
  return (Layer*) scrollableLayer->getChildByTag(OBJECTS_LAYER_TAG);
}

Layer* GameplayScene::_getControlsLayer() {
  auto scrollableLayer = this->_getScrollableLayer();
  return (Layer*) scrollableLayer->getChildByTag(CONTROLS_LAYER_TAG);
}

Vec2 GameplayScene::_positionInScene(Vec2 gameCoordinate) {
  auto centerPosition = INITIAL_POSITION;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = gameCoordinate.x - centerPosition.x;
  auto offsetY = gameCoordinate.y - centerPosition.y;
  
  return Vec2(centerOfScene.x + offsetX * TILE_DIMENSION,
              centerOfScene.y + offsetY * TILE_DIMENSION);
}

Vec2 GameplayScene::_positionInGameCoordinate(Vec2 scenePosition) {
  auto centerPosition = INITIAL_POSITION;
  auto centerOfScene = this->_centerOfScene();
  
  auto offsetX = scenePosition.x - centerOfScene.x;
  auto offsetY = scenePosition.y - centerOfScene.y;
  
  auto halfTileDimension = TILE_DIMENSION / 2;
  
  offsetX > halfTileDimension ? offsetX += halfTileDimension : offsetX -= halfTileDimension;
  offsetY > halfTileDimension ? offsetY += halfTileDimension : offsetY -= halfTileDimension;
  
  return Vec2(centerPosition.x + int(offsetX / TILE_DIMENSION),
              centerPosition.y + int(offsetY / TILE_DIMENSION));
}

void GameplayScene::_adjustCharacterDiceSpritePosition() {
  auto sprite = this->_getObjectsLayer()->getChildByTag(CHARACTER_DICE_SPRITE_TAG);
  auto characterPosition = this->getGame()->getCharacterPosition();
  sprite->setPosition(this->_positionInScene(characterPosition));
}

void GameplayScene::_addOverlayWithVisibleNodes(Vector<Node *> visibleNodes) {
  auto objectsLayer = this->_getObjectsLayer();
  auto scrollableLayer = this->_getScrollableLayer();
  
  auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
  overlayLayer->setTag(OVERLAY_LAYER_TAG);
  overlayLayer->setPosition(Vec2(-scrollableLayer->getPosition().x,
                                 -scrollableLayer->getPosition().y));
  
  objectsLayer->addChild(overlayLayer, OVERLAY_Z_ORDER);
  
  auto fadeIn = FadeTo::create(OVERLAY_DURATION, OVERLAY_OPACITY);
  overlayLayer->runAction(fadeIn);
  
  for (auto visibleNode : visibleNodes) {
    auto newZOrder = visibleNode->getLocalZOrder() + OVERLAY_Z_ORDER;
    visibleNode->setLocalZOrder(newZOrder);
  }
  
  this->setInteractableNodes(visibleNodes);
}

void GameplayScene::_removeOverlay() {
  this->_disableInteractions();
  
  auto overlayLayer = this->_getObjectsLayer()->getChildByTag(OVERLAY_LAYER_TAG);
  
  auto fadeOut = FadeOut::create(OVERLAY_DURATION);
  auto changeLayer = CallFunc::create([=]() {
    for (auto node : this->getInteractableNodes()) {
      auto oldZOrder = node->getLocalZOrder() - OVERLAY_Z_ORDER;
      node->setLocalZOrder(oldZOrder);
    }
  });
  auto removeSelf = RemoveSelf::create();
  auto animationEnded = CallFunc::create([=]() {
    this->_enableInteractions();
  });
  
  overlayLayer->runAction(Sequence::create(fadeOut, changeLayer, removeSelf, animationEnded, NULL));
}

Vec2 GameplayScene::_centerOfScene() {
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  return Vec2(visibleSize.width / 2 + visibleOrigin.x,
              visibleSize.height / 2 + visibleOrigin.y);
}

Node* GameplayScene::_getNodeForCharacterPosition() {
  auto position = this->getGame()->getCharacterPosition();
  auto name = this->getGame()->getDungeon()->nameForPosition(position);
  return this->_getObjectsLayer()->getChildByName(name);
}

Vector<Node*> GameplayScene::_getNodesForAdjacentCharacterPosition() {
  Node* activeLayer = this->_getObjectsLayer();
  auto overlayLayer = this->getChildByTag(OVERLAY_LAYER_TAG);
  if (overlayLayer) {
    activeLayer = overlayLayer;
  }
  
  Vector<Node*> nodes;
  
  auto position = this->getGame()->getCharacterPosition();
  auto adjacentPositions = this->getGame()->getDungeon()->adjacentPositionsTo(position);
  for (auto adjacentPosition : adjacentPositions) {
    auto name = this->getGame()->getDungeon()->nameForPosition(adjacentPosition);
    nodes.pushBack(activeLayer->getChildByName(name));
  }
  
  return nodes;
}

bool GameplayScene::_isInteractionEnabled() {
  return _userInteractionEnabled;
}

void GameplayScene::_disableInteractions() {
  _userInteractionEnabled = false;
}

void GameplayScene::_enableInteractions() {
  _userInteractionEnabled = true;
}

#pragma mark - CharacterMoveDelegate Methods

bool GameplayScene::canCharacterMove() {
  bool playerHasBoot = true;
  return this->_isInteractionEnabled() && playerHasBoot;
}

void GameplayScene::characterWillMove(CharacterDiceSprite* sprite) {
  Vector<Node*> visibleNodes;
  visibleNodes.pushBack(this->_getObjectsLayer()->getChildByTag(CHARACTER_DICE_SPRITE_TAG));
  visibleNodes.pushBack(this->_getNodeForCharacterPosition());
  visibleNodes.pushBack(this->_getNodesForAdjacentCharacterPosition());
  this->_addOverlayWithVisibleNodes(visibleNodes);
}

void GameplayScene::characterIsMovingToLocation(Vec2 location) {
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    Color3B color = Color3B::WHITE;
    
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      color = Color3B(170, 255, 170);
    }
    
    adjacentNode->setColor(color);
  }
}

bool GameplayScene::canCharacterMoveToLocation(Vec2 location) {
  bool canMove = false;
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    if (adjacentNode->getBoundingBox().containsPoint(location)) {
      canMove = true;
      break;
    }
  }
  
  return canMove;
}

void GameplayScene::characterMovedToLocation(CharacterDiceSprite* sprite, Vec2 location) {
  this->_removeOverlay();
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    adjacentNode->setColor(Color3B::WHITE);
  }
  
  auto newCoordinate = this->_positionInGameCoordinate(location);
  auto newPosition = this->_positionInScene(newCoordinate);
  
  auto moveNewPosition = MoveTo::create(RETURN_CHARACTER_DURATION, newPosition);
  auto actionEnded = CallFunc::create([=]() {
    this->getGame()->setCharacterPosition(newCoordinate);
  });
  sprite->runAction(Sequence::create(moveNewPosition, actionEnded, NULL));
}

void GameplayScene::characterDidNotMove(CharacterDiceSprite* sprite) {
  this->_removeOverlay();
  
  for (auto adjacentNode : this->_getNodesForAdjacentCharacterPosition()) {
    adjacentNode->setColor(Color3B::WHITE);
  }
  
  auto coordinate = this->getGame()->getCharacterPosition();
  auto scenePosition = this->_positionInScene(coordinate);
  
  auto moveBack = MoveTo::create(RETURN_CHARACTER_DURATION, scenePosition);
  sprite->runAction(moveBack);
}
