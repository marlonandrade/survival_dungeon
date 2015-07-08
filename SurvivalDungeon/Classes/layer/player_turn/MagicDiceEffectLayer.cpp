//
//  MagicDiceEffectLayer.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "MagicDiceEffectLayer.h"

#include "Definitions.h"
#include "Images.h"

#include "Dice.h"
#include "ActionDice.h"

#include "ActionDiceSprite.h"
#include "DockableContainer.h"
#include "GameplayLayer.h"

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

void MagicDiceEffectLayer::triggerEffect(ActionDice* magicDice, ActionDice* targetDice, Layer* layer) {
  this->setMagicDice(magicDice);
  this->setTargetDice(targetDice);
  
  layer->addChild(this);
  this->setLocalZOrder(MAX_Z_ORDER);
  
  auto sprite = targetDice->getSprite();
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
    if (image != targetDice->getSelectedFace()->getImagePath()) {
      auto sprite = Sprite::create(image);
      sprite->setPosition(nodePosition);
      sprite->setName(image);
      
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
  touchListener->onTouchEnded = CC_CALLBACK_2(MagicDiceEffectLayer::_onTouchEnded, this);
  
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool MagicDiceEffectLayer::_onTouchBegan(Touch* touch, Event* event) {
  return true;
}

void MagicDiceEffectLayer::_onTouchEnded(Touch* touch, Event* event) {
  Node* selectedDice = nullptr;
  
  auto touchLocation = touch->getLocation();
  for (auto child : this->getChildren()) {
    if (!(IS(child, Layer))) {
      if (child != this->getTargetDice()->getSprite() &&
          child->getBoundingBox().containsPoint(touchLocation)) {
        selectedDice = child;
        break;
      }
    }
  }
  
  auto sprite = this->getTargetDice()->getSprite();
  sprite->setLocalZOrder(sprite->getLocalZOrder() + 100);
  
  auto position = 0;
  auto children = this->getChildren();
  children.reverse();
  
  if (selectedDice) {
    for (auto child : children) {
      if (IS(child, Sprite) && child != selectedDice) {
        auto delay = DelayTime::create(MAGIC_DICE_DURATION * position);
        auto moveBack = EaseOut::create(MoveTo::create(MAGIC_DICE_DURATION, sprite->getPosition()), 5);
        
        child->runAction(Sequence::create(delay, moveBack, NULL));
        
        position++;
      }
    }
    
    auto delay = DelayTime::create(MAGIC_DICE_DURATION * (position - 1));
    auto fadeOut = FadeOut::create(MAGIC_DICE_DURATION);
    auto dockMagicDice = CallFunc::create([=]{
      auto magicSprite = (ActionDiceSprite*) this->getMagicDice()->getSprite();
      auto gameplayLayer = (GameplayLayer*) this->getParent();
      
      gameplayLayer->dockActionDice(magicSprite);
    });
    auto fadeAndDockMagicDice = Spawn::create(fadeOut, dockMagicDice, NULL);
    
    auto removeFromParent = CallFunc::create([=]{
      OverlayUtil::removeOverlay(this);
      
      sprite->setLocalZOrder(ACTION_DICE_Z_ORDER);
      sprite->retain();
      sprite->removeFromParent();
      this->getParent()->addChild(sprite);
      sprite->release();
      
      DiceFace* choosenFace;
      for (auto face : this->getTargetDice()->getFaces()) {
        if (face->getImagePath() == selectedDice->getName()) {
          choosenFace = face;
        }
      }
      this->getTargetDice()->setSelectedFace(choosenFace, false);
      
      this->removeFromParent();
    });
    
    this->runAction(Sequence::create(delay, fadeAndDockMagicDice, removeFromParent, NULL));
    log("todos dados animados exceto o selecionado!");
  } else {
    for (auto child : children) {
      if (IS(child, Sprite)) {
        auto delay = DelayTime::create(MAGIC_DICE_DURATION * position);
        auto moveBack = EaseOut::create(MoveTo::create(MAGIC_DICE_DURATION, sprite->getPosition()), 5);
        
        child->runAction(Sequence::create(delay, moveBack, NULL));
        
        position++;
      }
    }
    
    auto delay = DelayTime::create(MAGIC_DICE_DURATION * (position - 1));
    auto fadeOut = FadeOut::create(MAGIC_DICE_DURATION);
    auto restoreMagicPosition = CallFunc::create([=]{
      auto magicSprite = (ActionDiceSprite*) this->getMagicDice()->getSprite();
      magicSprite->restoreOriginalPosition();
    });
    
    auto fadeAndRestoreMagicDice = Spawn::create(fadeOut, restoreMagicPosition, NULL);
    
    auto removeFromParent = CallFunc::create([=]{
      OverlayUtil::removeOverlay(this);
      
      sprite->setLocalZOrder(ACTION_DICE_Z_ORDER);
      sprite->retain();
      sprite->removeFromParent();
      this->getParent()->addChild(sprite);
      sprite->release();
      
      this->removeFromParent();
    });
    
    this->runAction(Sequence::create(delay, fadeAndRestoreMagicDice, removeFromParent, NULL));
  }
}
