//
//  MagicDiceEffectLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "MagicDiceEffectLayer.h"

#include "Definitions.h"
#include "Images.h"

#include "Dice.h"

#include "OverlayUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

bool MagicDiceEffectLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->_setupTouchListener();
  
  return true;
}

void MagicDiceEffectLayer::triggerEffectOnTarget(Dice* dice, Layer* layer) {
  layer->addChild(this);
  this->setLocalZOrder(MAX_Z_ORDER);
  
  auto sprite = dice->getSprite();
  auto nodePosition = sprite->getPosition();
  
  sprite->retain();
  sprite->removeFromParent();
  this->addChild(sprite);
  sprite->release();
  
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
    if (image != dice->getSelectedFace()->getImagePath()) {
      auto sprite = Sprite::create(image);
      sprite->setPosition(nodePosition);
      
      this->addChild(sprite);
      
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
    OverlayUtil::addOverlay(targetNodes, this);
  });
  
  this->runAction(Sequence::create(delay, callfunc, NULL));
}

#pragma mark - Private Interface

void MagicDiceEffectLayer::_setupTouchListener() {
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->setSwallowTouches(true);
  touchListener->onTouchBegan = CC_CALLBACK_2(MagicDiceEffectLayer::_onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(MagicDiceEffectLayer::_onTouchMoved, this);
  touchListener->onTouchEnded = CC_CALLBACK_2(MagicDiceEffectLayer::_onTouchEnded, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool MagicDiceEffectLayer::_onTouchBegan(Touch* touch, Event* event) {
  return true;
}

void MagicDiceEffectLayer::_onTouchMoved(Touch* touch, Event* event) {
  
}

void MagicDiceEffectLayer::_onTouchEnded(Touch* touch, Event* event) {
  Node* selectedDice = nullptr;
  
  auto touchLocation = touch->getLocation();
  for (auto child : this->getChildren()) {
    if (!(IS(child, Layer))) {
      if (child->getBoundingBox().containsPoint(touchLocation)) {
        selectedDice = child;
        break;
      }
    }
  }
  
  if (selectedDice) {
    log("modificar dado selecionado e 'gastar' magia");
  } else {
    log("desfazer e voltar magia pro lugar inicial");
  }
}