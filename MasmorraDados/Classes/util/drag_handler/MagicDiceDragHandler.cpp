//
//  MagicDiceDragHandler.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "MagicDiceDragHandler.h"

#include "Definitions.h"
#include "Images.h"

#include "OverlayUtil.h"

#include "ActionDiceDragData.h"

#include "ActionDiceSprite.h"

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

void MagicDiceDragHandler::dragEnded(ActionDiceDragData* data, Layer* layer) {
  auto sprite = data->getSprite();
  auto touch = data->getTouch();
  
  for (auto node : layer->getChildren()) {
    if (IS(node, ActionDiceSprite) && node != sprite) {
      auto targetDice = ((ActionDiceSprite*) node)->getDice();
      auto rect = node->getBoundingBox();
      
      if (rect.containsPoint(touch->getLocation())) {
        node->setColor(Color3B::WHITE);
        this->_triggerEffectOnTarget(targetDice, layer);
        break;
      }
    }
  }
}

#pragma mark - Private Interface

void MagicDiceDragHandler::_triggerEffectOnTarget(Dice* targetDice, Layer* layer) {
  auto sprite = targetDice->getSprite();
  auto nodePosition = sprite->getPosition();
  
  Vector<Node*> targetNodes;
  targetNodes.pushBack(sprite);
  
  std::vector<std::string> images;
  
  images.push_back(IMG_DICE_ACTION_BOOT);
  images.push_back(IMG_DICE_ACTION_BOW);
  images.push_back(IMG_DICE_ACTION_HEAL);
  images.push_back(IMG_DICE_ACTION_SHIELD);
  images.push_back(IMG_DICE_ACTION_SWORD);
  
  int position = 0;
  for (auto image : images) {
    if (image != targetDice->getSelectedFace()->getImagePath()) {
      auto sprite = Sprite::create(image);
      sprite->setPosition(nodePosition);
      
      layer->addChild(sprite);
      
      targetNodes.pushBack(sprite);
      
      auto yOffset = (sprite->getContentSize().height + 2) * (position + 1);
      auto newPosition = Vec2(nodePosition.x, nodePosition.y + yOffset);
      
      auto delay = DelayTime::create(MAGIC_DICE_DURATION * position);
      auto adjustPosition = EaseOut::create(MoveTo::create(MAGIC_DICE_DURATION, newPosition), 5);
      
      sprite->runAction(Sequence::create(delay, adjustPosition, NULL));
      
      position++;
    }
  }
  
  auto delay = DelayTime::create(OVERLAY_DURATION);
  auto callfunc = CallFunc::create([=] {
    OverlayUtil::addOverlay(targetNodes, layer);
  });
  
  layer->runAction(Sequence::create(delay, callfunc, NULL));
}