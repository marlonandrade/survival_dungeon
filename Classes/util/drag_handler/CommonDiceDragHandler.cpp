//
//  CommonDiceDragHandler.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "CommonDiceDragHandler.h"

#include "Definitions.h"

#include "ActionDiceDragData.h"

#include "DockableContainer.h"
#include "GameplayLayer.h"

#include "OverlayUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

void CommonDiceDragHandler::dragStarted(ActionDiceDragData* data,
                                        GameplayLayer* layer,
                                        DockableContainer* dockableContainer) {
  auto sprite = data->getSprite();
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  auto dockableNodes = dockableContainer->getDockableNodes();
  
  targetNodes.pushBack(dockableContainer);
  targetNodes.pushBack(dockableNodes);
  
  for (auto node : dockableNodes) {
    if (node->getChildren().size() > 0 &&
        node->getBoundingBox().containsPoint(dockableLocation)) {
      sprite->undock(layer);
      break;
    }
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void CommonDiceDragHandler::dragMoved(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  auto dockableNodes = dockableContainer->getDockableNodes();
  
  for (auto node : dockableNodes) {
    auto color = Color3B::WHITE;
    auto rect = node->getBoundingBox();
    
    rect.origin -= Vec2(DOCKABLE_HIDDEN_MARGIN, 0);
    rect.size = rect.size + Size(DOCKABLE_HIDDEN_MARGIN * 2, 0);
    
    if (node->getChildren().size() == 0 &&
        rect.containsPoint(dockableLocation)) {
      color = OK_COLOR;
    }
    
    node->setColor(color);
  }
}

bool CommonDiceDragHandler::dragEnded(ActionDiceDragData* data,
                                      GameplayLayer* layer,
                                      DockableContainer* dockableContainer) {
  auto docked = false;
  
  auto sprite = data->getSprite();
  
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  auto dockableNodes = dockableContainer->getDockableNodes();
  
  for (auto node : dockableNodes) {
    auto rect = node->getBoundingBox();
    
    rect.origin -= Vec2(DOCKABLE_HIDDEN_MARGIN, 0);
    rect.size = rect.size + Size(DOCKABLE_HIDDEN_MARGIN * 2, 0);
    
    if (node->getChildren().size() == 0 &&
        rect.containsPoint(dockableLocation)) {
      docked = true;
      node->setColor(Color3B::WHITE);
      
      sprite->dockOnNode(node);
      
      break;
    }
  }
  
  return docked;
}
