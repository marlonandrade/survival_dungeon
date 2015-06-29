//
//  AttackDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/27/15.
//
//

#include "AttackDiceDragHandler.h"

#include "Definitions.h"

#include "ActionDiceDragData.h"

#include "DungeonLayer.h"
#include "DungeonRoomSprite.h"
#include "GameplayLayer.h"
#include "GameplayScene.h"

#include "Game.h"

#include "HighlightUtil.h"
#include "OverlayUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

void AttackDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                        GameplayLayer* layer,
                                        DockableContainer* dockableContainer) {
  Vector<Node*> targetNodes;
  
  auto scene = (GameplayScene*) layer->getScene();
  auto dungeonLayer = scene->getDungeonLayer();
  
  auto game = Game::getInstance();
  auto characterCoordinate = game->getCharacterCoordinate();
  auto room = game->getDungeon()->getRoomForCoordinate(characterCoordinate);
  
  for (auto monster : room->getMonsters()) {
    auto monsterSprite = monster->getSprite();
    
    auto position = monsterSprite->getPosition() -
      Vec2(TILE_DIMENSION / 2, TILE_DIMENSION / 2) +
      monsterSprite->getParent()->getPosition() +
      dungeonLayer->getParent()->getPosition();
    monsterSprite->setPosition(position);
    
    monsterSprite->retain();
    monsterSprite->removeFromParent();
    layer->addChild(monsterSprite);
    monsterSprite->release();
    
    targetNodes.pushBack(monsterSprite);
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void AttackDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto touch = data->getTouch();
  
  auto game = Game::getInstance();
  auto characterCoordinate = game->getCharacterCoordinate();
  auto room = game->getDungeon()->getRoomForCoordinate(characterCoordinate);
  
  for (auto monster : room->getMonsters()) {
    HighlightUtil::highlighNode(monster->getSprite(), touch);
  }
}

bool AttackDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto docked = false;
  
  auto touch = data->getTouch();
  
  auto scene = (GameplayScene*) layer->getScene();
  auto dungeonLayer = scene->getDungeonLayer();
  
  auto game = Game::getInstance();
  auto characterCoordinate = game->getCharacterCoordinate();
  auto room = game->getDungeon()->getRoomForCoordinate(characterCoordinate);
  auto roomSprite = dungeonLayer->getRoomSpriteForCharacterCoordinate();
  
  for (auto monster : room->getMonsters()) {
    auto monsterSprite = monster->getSprite();
    auto rect = monsterSprite->getBoundingBox();
    
    if (rect.containsPoint(touch->getLocation())) {
      monsterSprite->setColor(Color3B::WHITE);
      
      // TODO: dar dano!
      // verificar tipo de dado para ver efeito
      // espada
      // 2 espada + escudo
      // arco
      
      docked = true;
      break;
    }
    
    auto position = monsterSprite->getPosition() +
      Vec2(TILE_DIMENSION / 2, TILE_DIMENSION / 2) -
      roomSprite->getPosition() -
      dungeonLayer->getParent()->getPosition();
    monsterSprite->setPosition(position);
    
    monsterSprite->retain();
    monsterSprite->removeFromParent();
    roomSprite->addChild(monsterSprite);
    monsterSprite->release();
  }
  
  return docked;
}