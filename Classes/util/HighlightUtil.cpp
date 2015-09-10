//
//  HighlightUtil.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/7/15.
//
//

#include "HighlightUtil.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

void HighlightUtil::highlighNode(Node* node, Touch* touch) {
  auto color = Color3B::WHITE;
  auto rect = node->getBoundingBox();
  
  if (rect.containsPoint(touch->getLocation())) {
    color = OK_COLOR;
  }
  
  node->setColor(color);
}
