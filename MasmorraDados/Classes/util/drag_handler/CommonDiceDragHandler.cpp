//
//  CommonDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "CommonDiceDragHandler.h"

#include "Definitions.h"

#include "ActionDiceDragData.h"

#include "OverlayUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

void CommonDiceDragHandler::dragStarted(ActionDiceDragData* data, Layer* layer,
                                        Node* dockableContainer, Vector<Node*> dockableNodes) {
  auto sprite = data->getSprite();
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  
  targetNodes.pushBack(dockableNodes);
  targetNodes.pushBack(dockableContainer);
  
  for (auto node : dockableNodes) {
    if (node->getChildren().size() > 0 &&
        node->getBoundingBox().containsPoint(dockableLocation)) {
      sprite->undock(layer);
      break;
    }
  }
  
  OverlayUtil::addOverlay(targetNodes, layer);
}

void CommonDiceDragHandler::dragMoved(ActionDiceDragData* data, Layer* layer,
                                      Node* dockableContainer, Vector<Node*> dockableNodes) {
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  
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

bool CommonDiceDragHandler::dragEnded(ActionDiceDragData* data, Layer* layer,
                                      Node* dockableContainer, Vector<Node*> dockableNodes) {
  auto docked = false;
  
  auto sprite = data->getSprite();
  
  auto dockableLocation = dockableContainer->convertTouchToNodeSpaceAR(data->getTouch());
  
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