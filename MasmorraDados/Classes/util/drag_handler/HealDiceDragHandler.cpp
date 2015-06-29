//
//  HealDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#include "HealDiceDragHandler.h"

#include "Game.h"

#include "DungeonLayer.h"
#include "DungeonRoomSprite.h"
#include "GameplayLayer.h"
#include "GameplayScene.h"

#include "ActionDiceDragData.h"

#include "HighlightUtil.h"
#include "OverlayUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

void HealDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  Vector<Node*> targetNodes;
  
  auto game = Game::getInstance();
  auto character = game->getPlayer()->getCharacter();
  if (!character->isLifeFull()) {
    auto scene = (GameplayScene*) layer->getScene();
    auto dungeonLayer = scene->getDungeonLayer();
    
    auto character = game->getPlayer()->getCharacter();
    auto characterSprite = character->getSprite();
    
    auto position = characterSprite->getPosition() -
        Vec2(TILE_DIMENSION / 2, TILE_DIMENSION / 2) +
        characterSprite->getParent()->getPosition() +
        dungeonLayer->getParent()->getPosition();
    characterSprite->setPosition(position);
    
    characterSprite->retain();
    characterSprite->removeFromParent();
    layer->addChild(characterSprite);
    characterSprite->release();
    
    targetNodes.pushBack(characterSprite);
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void HealDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                    GameplayLayer* layer,
                                    DockableContainer* dockableContainer) {
  auto touch = data->getTouch();
  auto game = Game::getInstance();
  auto character = game->getPlayer()->getCharacter();
  if (!character->isLifeFull()) {
    HighlightUtil::highlighNode(character->getSprite(), touch);
  }
}

bool HealDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                    GameplayLayer* layer,
                                    DockableContainer* dockableContainer) {
  auto docked = false;
  
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  auto game = Game::getInstance();
  auto character = game->getPlayer()->getCharacter();
  if (!character->isLifeFull()) {
    auto scene = (GameplayScene*) layer->getScene();
    auto dungeonLayer = scene->getDungeonLayer();
    
    auto dungeonRoom = dungeonLayer->getRoomSpriteForCharacterCoordinate();
    
    auto characterSprite = character->getSprite();
    
    auto rect = characterSprite->getBoundingBox();
    if (rect.containsPoint(touch->getLocation())) {
      characterSprite->setColor(Color3B::WHITE);
      
      character->heal(1);
      layer->dockActionDice(sprite);
      
      docked = true;
    }
    
    characterSprite->setLocalZOrder(CHARACTER_DICE_Z_ORDER);
    
    auto position = characterSprite->getPosition() +
        Vec2(TILE_DIMENSION / 2, TILE_DIMENSION / 2) -
        dungeonRoom->getPosition() -
        dungeonLayer->getParent()->getPosition();
    characterSprite->setPosition(position);
    
    characterSprite->retain();
    characterSprite->removeFromParent();
    dungeonRoom->addChild(characterSprite);
    characterSprite->release();
  }
  
  return docked;
}