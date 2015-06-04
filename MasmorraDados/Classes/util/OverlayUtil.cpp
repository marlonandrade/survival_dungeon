//
//  OverlayUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "OverlayUtil.h"

#include "Definitions.h"
#include "NodeNames.h"

USING_NS_CC;

#pragma mark - Public Interface

void OverlayUtil::addOverlay(Vector<Node*> nodes, Node* parentNode) {
  OverlayUtil::addOverlay(nodes, parentNode, Vec2::ZERO);
}

void OverlayUtil::addOverlay(Vector<Node*> nodes, Node* parentNode, Vec2 position) {
  auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
  overlayLayer->setName(OVERLAY_LAYER_NAME);
  overlayLayer->setPosition(position);
  
  for (auto node : nodes) {
    auto newZOrder = node->getLocalZOrder() + OVERLAY_Z_ORDER;
    node->setLocalZOrder(newZOrder);
  }
  
  parentNode->addChild(overlayLayer, OVERLAY_Z_ORDER - 1);
  
  auto fadeIn = FadeTo::create(OVERLAY_DURATION, OVERLAY_OPACITY);
  overlayLayer->runAction(fadeIn);
}

void OverlayUtil::removeOverlay(Node* parentNode) {
  auto overlayLayer = parentNode->getChildByName(OVERLAY_LAYER_NAME);
  
  auto fadeOut = FadeOut::create(OVERLAY_DURATION);
  auto changeLayer = CallFunc::create([=]() {
    for (auto node : parentNode->getChildren()) {
      if (node->getLocalZOrder() > overlayLayer->getLocalZOrder()) {
        auto oldZOrder = node->getLocalZOrder() - OVERLAY_Z_ORDER;
        node->setLocalZOrder(oldZOrder);
      }
    }
  });
  auto removeSelf = RemoveSelf::create();
  
  overlayLayer->runAction(Sequence::create(fadeOut, changeLayer, removeSelf, NULL));
}