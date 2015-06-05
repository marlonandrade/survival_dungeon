//
//  MagicDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "MagicDiceDragHandler.h"

#include "Definitions.h"

#include "OverlayUtil.h"

#include "ActionDiceDragData.h"

#include "ActionDiceSprite.h"
#include "MagicDiceEffectLayer.h"

#include "Dice.h"

USING_NS_CC;

#pragma mark - Public Interface

void MagicDiceDragHandler::dragStarted(ActionDiceDragData* data, Layer* layer) {
  Vector<Node*> targetNodes;
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      targetNodes.pushBack(node);
    }
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void MagicDiceDragHandler::dragMoved(ActionDiceDragData* data, Layer* layer) {
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite) && node != sprite) {
      auto color = Color3B::WHITE;
      auto rect = node->getBoundingBox();
      
      if (rect.containsPoint(touch->getLocation())) {
        color = OK_COLOR;
      }
      
      node->setColor(color);
    }
  }
}

bool MagicDiceDragHandler::dragEnded(ActionDiceDragData* data, Layer* layer) {
  auto docked = false;
  
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite) && node != sprite) {
      auto actionSprite = (ActionDiceSprite*) node;
      auto rect = node->getBoundingBox();
      
      if (rect.containsPoint(touch->getLocation())) {
        node->setColor(Color3B::WHITE);
        
        auto magicDice = (ActionDice*) sprite->getDice();
        auto targetDice = (ActionDice*) actionSprite->getDice();
        
        MagicDiceEffectLayer::create()->triggerEffect(magicDice, targetDice, layer);
        
        docked = true;
        break;
      }
    }
  }
  
  return docked;
}
