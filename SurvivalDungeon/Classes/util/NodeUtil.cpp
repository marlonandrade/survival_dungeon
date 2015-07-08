//
//  NodeUtil.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/24/15.
//
//

#include "NodeUtil.h"

USING_NS_CC;

void NodeUtil::stopAllActionsRecursive(Node* node) {
  node->stopAllActions();
  
  for (auto child : node->getChildren()) {
    NodeUtil::stopAllActionsRecursive(child);
  }
}
