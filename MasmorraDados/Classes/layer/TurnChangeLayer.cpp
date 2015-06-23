//
//  TurnChangeLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#include "TurnChangeLayer.h"

#include "Definitions.h"
#include "Images.h"
#include "NodeNames.h"

#include "PositionUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

bool TurnChangeLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(TURN_CHANGE_LAYER_NAME);
  this->_setupChildren();
  
  return true;
}

void TurnChangeLayer::showPlayerTurnInfo() {
  this->_showInfo(this->getPlayerInfo());
}

void TurnChangeLayer::showDungeonTurnInfo() {
  this->_showInfo(this->getDungeonInfo());
}

#pragma mark - Private Interface

void TurnChangeLayer::_setupChildren() {
  auto overlayLayer = LayerColor::create(Color4B(0, 0, 0, 0));
  overlayLayer->setName(OVERLAY_LAYER_NAME);
  this->addChild(overlayLayer);
  
  auto sprite = Sprite::create();
  sprite->setName(TURN_CHANGE_SPRITE_NAME);
  sprite->setPosition(PositionUtil::visibleCenter());
  sprite->setScale(0.5, 0.5);
  sprite->setOpacity(0);
  this->addChild(sprite);
  
  this->setPlayerInfo(Sprite::create(IMG_TURN_PLAYER));
  this->setDungeonInfo(Sprite::create(IMG_TURN_DUNGEON));
}

LayerColor* TurnChangeLayer::_getOverlayLayer() {
  return (LayerColor*) this->getChildByName(OVERLAY_LAYER_NAME);
}

Node* TurnChangeLayer::_getInfo() {
  return (Node*) this->getChildByName(TURN_CHANGE_SPRITE_NAME);
}

void TurnChangeLayer::_showInfo(Sprite* infoSprite) {
  auto overlay = this->_getOverlayLayer();
  auto info = this->_getInfo();
  
  info->removeAllChildren();
  info->addChild(infoSprite);
  
  auto overlayFadeDuration = 0.2;
  auto overlayDelayDuration = TURN_INFO_DURATION - overlayFadeDuration * 2;
  
  auto delayAndFadeOut = Sequence::create(FadeTo::create(overlayFadeDuration, OVERLAY_OPACITY),
                                          DelayTime::create(overlayDelayDuration),
                                          FadeOut::create(overlayFadeDuration), NULL);
  
  auto infoFadeInDuration = 0.2;
  auto infoFadeOutDuration = 0.2;
  auto infoDelayDuration = TURN_INFO_DURATION - infoFadeInDuration - infoFadeOutDuration;
  
  auto fadeInTurnInfo = Spawn::create(FadeIn::create(infoFadeInDuration),
                                      EaseBackOut::create(ScaleTo::create(infoFadeInDuration, 1)), NULL);
  auto fadeOutTurnInfo = Spawn::create(FadeOut::create(infoFadeOutDuration),
                                       EaseBackIn::create(ScaleTo::create(infoFadeOutDuration + 0.2, 0)), NULL);
  
  overlay->runAction(delayAndFadeOut);
  info->runAction(Sequence::create(fadeInTurnInfo,
                                   DelayTime::create(infoDelayDuration),
                                   fadeOutTurnInfo, NULL));
}