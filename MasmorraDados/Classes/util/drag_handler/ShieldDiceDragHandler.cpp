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

#include "DiceUtil.h"
#include "OverlayUtil.h"

#include "ActionDiceDragData.h"

#include "ActionDiceSprite.h"
#include "DockableContainer.h"
#include "GameplayLayer.h"

#include "Dice.h"

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
        
        // TODO: verificar se jogador está tomando dano
        // TODO: se sim, adicionar o jogador também
      }
    }
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void ShieldDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto touch = data->getTouch();
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      auto diceSprite = (ActionDiceSprite*) node;
      auto dice = diceSprite->getDice();
      
      if (DiceUtil::isSwordDice(dice)) {
        auto color = Color3B::WHITE;
        auto rect = node->getBoundingBox();
        
        if (rect.containsPoint(touch->getLocation())) {
          color = OK_COLOR;
        }
        
        node->setColor(color);
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
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      auto diceSprite = (ActionDiceSprite*) node;
      auto dice = diceSprite->getDice();
      
      if (DiceUtil::isSwordDice(dice)) {
        auto rect = node->getBoundingBox();
        
        if (rect.containsPoint(touch->getLocation())) {
          node->setColor(Color3B::WHITE);
          
          auto swordAndShield = DiceFace::createWithImagePath(IMG_DICE_ACTION_SWORD_AND_SHIELD);
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