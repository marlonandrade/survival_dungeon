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

#include "DiceUtil.h"
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
  
  for (auto monsterDice : room->getMonsters()) {
    auto monsterSprite = monsterDice->getSprite();
    
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
  
  for (auto monsterDice : room->getMonsters()) {
    HighlightUtil::highlighNode(monsterDice->getSprite(), touch);
  }
}

bool AttackDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto docked = false;
  
  auto diceSprite = data->getSprite();
  auto touch = data->getTouch();
  
  auto scene = (GameplayScene*) layer->getScene();
  auto dungeonLayer = scene->getDungeonLayer();
  
  auto game = Game::getInstance();
  
  auto character = game->getPlayer()->getCharacter();
  auto characterSprite = character->getSprite();
  auto characterCoordinate = game->getCharacterCoordinate();
  
  auto room = game->getDungeon()->getRoomForCoordinate(characterCoordinate);
  auto roomSprite = dungeonLayer->getRoomSpriteForCharacterCoordinate();
  
  for (auto monsterDice : room->getMonsters()) {
    auto monsterSprite = monsterDice->getSprite();
    
    auto rect = monsterSprite->getBoundingBox();
    if (rect.containsPoint(touch->getLocation())) {
      monsterSprite->setColor(Color3B::WHITE);
      
      auto dice = diceSprite->getDice();
      if (DiceUtil::isSwordDice(dice)) {
        monsterDice->takeDamage(1, CombatModeMelee);
      } else if (DiceUtil::isSwordAndShieldDice(dice)) {
        monsterDice->takeDamage(2, CombatModeMelee);
        characterSprite->defendDamage(1);
      } else if (DiceUtil::isBowDice(dice)) {
        monsterDice->takeDamage(1, CombatModeRanged);
      }
      
      layer->dockActionDice(diceSprite);
      
      docked = true;
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