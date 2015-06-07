//
//  ShieldDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/6/15.
//
//

#include "ShieldDiceDragHandler.h"

USING_NS_CC;

#include "Definitions.h"
#include "Images.h"
#include "NodeNames.h"

#include "DiceUtil.h"
#include "HighlightUtil.h"
#include "OverlayUtil.h"

#include "ActionDiceDragData.h"

#include "ActionDiceSprite.h"
#include "CharacterDiceSprite.h"
#include "DockableContainer.h"
#include "DungeonLayer.h"
#include "DungeonRoomSprite.h"
#include "GameplayLayer.h"
#include "GameplayScene.h"

#include "Dice.h"
#include "Game.h"

#pragma mark - Public Interface;

void ShieldDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                        GameplayLayer* layer,
                                        DockableContainer* dockableContainer) {
  Vector<Node*> targetNodes;
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      auto diceSprite = (ActionDiceSprite*) node;
      auto dice = diceSprite->getDice();
      
      if (DiceUtil::isSwordDice(dice)) {
        targetNodes.pushBack(node);
      }
    }
  }
  
  auto game = Game::getInstance();
  if (game->getDamageTaken() > 0) {
    auto scene = (GameplayScene*) layer->getScene();
    auto dungeonLayer = scene->getDungeonLayer();
    
    auto dungeonRoom = dungeonLayer->getRoomSpriteForCharacterCoordinate();
    auto characterSprite = dungeonRoom->getCharacterDiceSprite();
    
    log("%d", characterSprite->getLocalZOrder());
    
    auto position = characterSprite->getPosition() -
        Vec2(TILE_DIMENSION / 2, TILE_DIMENSION / 2) +
        dungeonRoom->getPosition() +
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

void ShieldDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto touch = data->getTouch();
  
  auto game = Game::getInstance();
  if (game->getDamageTaken() > 0) {
    auto characterSprite = layer->getChildByName<CharacterDiceSprite*>(CHARACTER_DICE_SPRITE_NAME);
    HighlightUtil::highlighNode(characterSprite, touch);
  }
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      auto diceSprite = (ActionDiceSprite*) node;
      auto dice = diceSprite->getDice();
      
      if (DiceUtil::isSwordDice(dice)) {
        HighlightUtil::highlighNode(node, touch);
      }
    }
  }
}

bool ShieldDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto docked = false;
  
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  auto game = Game::getInstance();
  if (game->getDamageTaken() > 0) {
    auto scene = (GameplayScene*) layer->getScene();
    auto dungeonLayer = scene->getDungeonLayer();
    
    auto dungeonRoom = dungeonLayer->getRoomSpriteForCharacterCoordinate();
    auto characterSprite = layer->getChildByName<CharacterDiceSprite*>(CHARACTER_DICE_SPRITE_NAME);
    
    characterSprite->setLocalZOrder(CHARACTER_DICE_Z_ORDER);
    characterSprite->setColor(Color3B::WHITE);
    
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
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      auto diceSprite = (ActionDiceSprite*) node;
      auto dice = diceSprite->getDice();
      
      if (DiceUtil::isSwordDice(dice)) {
        auto rect = node->getBoundingBox();
        
        if (rect.containsPoint(touch->getLocation())) {
          node->setColor(Color3B::WHITE);
          
          auto swordAndShield = DiceFace::create(IMG_DICE_ACTION_SWORD_AND_SHIELD);
          dice->setSelectedFace(swordAndShield, false);
          layer->dockActionDice(sprite);
          
          docked = true;
          break;
        }
      }
    }
  }
  
  return docked;
}