//
//  MagicDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "MagicDiceDragHandler.h"

#include "Definitions.h"

#include "HighlightUtil.h"
#include "OverlayUtil.h"

#include "ActionDiceDragData.h"

#include "ActionDiceSprite.h"
#include "DockableContainer.h"
#include "GameplayLayer.h"
#include "MagicDiceEffectLayer.h"

#include "Dice.h"

USING_NS_CC;

#pragma mark - Public Interface

void MagicDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                       GameplayLayer* layer,
                                       DockableContainer* dockableContainer) {
  Vector<Node*> targetNodes;
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite)) {
      targetNodes.pushBack(node);
    }
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void MagicDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                     GameplayLayer* layer,
                                     DockableContainer* dockableContainer) {
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite) && node != sprite) {
      HighlightUtil::highlighNode(node, touch);
    }
  }
}

bool MagicDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                     GameplayLayer* layer,
                                     DockableContainer* dockableContainer) {
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
