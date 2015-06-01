//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "ActionDiceLayer.h"
#include "BackgroundLayer.h"
#include "DungeonLayer.h"
#include "PlayerSkillsLayer.h"
#include "ScrollableLayer.h"

#include "ActionDiceSprite.h"
#include "CharacterDiceSprite.h"

#include "RoomPlacementData.h"

#include "CoordinateUtil.h"
#include "PositionUtil.h"

#include "DungeonTurn.h"
#include "InitialTurn.h"
#include "PlayerTurn.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->_adjustInitialLayers();
  this->_setupEventHandlers();
  
  Game::getInstance()->setupCharacterInitialCoordinate();
  
  return true;
}

#pragma mark - Private Interface

void GameplayScene::_adjustInitialLayers() {
  auto dungeonLayer = DungeonLayer::create();
  auto backgroundLayer = BackgroundLayer::create();
  
  auto scrollableLayer = ScrollableLayer::createWithDungeon(Game::getInstance()->getDungeon());
  scrollableLayer->addChild(backgroundLayer, -10);
  scrollableLayer->addChild(dungeonLayer, 0);
  
  this->addChild(scrollableLayer, 0);
  this->addChild(this->_createControlsLayer(), 1);
}

void GameplayScene::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto actionDicesRolledCallback = CC_CALLBACK_1(GameplayScene::_handleActionDicesRolled, this);
  this->setActionDicesRolledListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICES_ROLLED, actionDicesRolledCallback)
  );
  
  auto turnHasStartedCallback = CC_CALLBACK_1(GameplayScene::_handleTurnHasStarted, this);
  this->setTurnHasStartedListener(
    dispatcher->addCustomEventListener(EVT_TURN_HAS_STARTED, turnHasStartedCallback)
  );
  
  auto turnHasEndedCallback = CC_CALLBACK_1(GameplayScene::_handleTurnHasEnded, this);
  this->setTurnHasEndedListener(
    dispatcher->addCustomEventListener(EVT_TURN_HAS_ENDED, turnHasEndedCallback)
  );
}

Layer* GameplayScene::_createControlsLayer() {
  auto controlsLayer = Layer::create();
  controlsLayer->setVisible(false);
  controlsLayer->setName(CONTROLS_LAYER_NAME);
  
  auto actionDiceLayer = ActionDiceLayer::createWithDices(Game::getInstance()->getActionDices());
  actionDiceLayer->setName(ACTION_DICE_LAYER_NAME);
  controlsLayer->addChild(actionDiceLayer);
  
  auto playerSkillsLayer = PlayerSkillsLayer::create();
  playerSkillsLayer->setName(PLAYER_SKILL_LAYER_NAME);
  playerSkillsLayer->setVisible(false);
  controlsLayer->addChild(playerSkillsLayer);
    
  return controlsLayer;
}

Layer* GameplayScene::_getScrollableLayer() {
  return (Layer*) this->getChildByName(SCROLLABLE_LAYER_NAME);
}

Layer* GameplayScene::_getControlsLayer() {
  return (Layer*) this->getChildByName(CONTROLS_LAYER_NAME);
}

void GameplayScene::_showPlayerTurnInfo() {
  this->_showTurnInfo(Sprite::create(IMG_TURN_PLAYER));
}

void GameplayScene::_showDungeonTurnInfo() {
  this->_showTurnInfo(Sprite::create(IMG_TURN_DUNGEON));
}

void GameplayScene::_showTurnInfo(cocos2d::Sprite *infoSprite) {
  auto layer = LayerColor::create(Color4B(0, 0, 0, 130));
  layer->setName(TURN_OVERLAY_LAYER_NAME);
  this->addChild(layer);
  
  infoSprite->setPosition(PositionUtil::visibleCenter());
  infoSprite->setScale(0.5, 0.5);
  infoSprite->setOpacity(0);
  layer->addChild(infoSprite);
  
  auto overlayFadeDuration = 0.2;
  auto overlayDelayDuration = TURN_INFO_DURATION - overlayFadeDuration;
  
  auto waitAndRemoveOverlay = Sequence::create(DelayTime::create(overlayDelayDuration),
                                               FadeTo::create(overlayFadeDuration, 0),
                                               CallFunc::create([&] {
    this->removeChildByName(TURN_OVERLAY_LAYER_NAME);
  }), NULL);
  
  
  auto infoFadeInDuration = 0.2;
  auto infoFadeOutDuration = 0.2;
  auto infoDelayDuration = TURN_INFO_DURATION - infoFadeInDuration - infoFadeOutDuration;
  
  auto fadeInTurnInfo = Spawn::create(FadeIn::create(infoFadeInDuration),
                                      EaseBackOut::create(ScaleTo::create(infoFadeInDuration, 1)), NULL);
  auto fadeOutTurnInfo = Spawn::create(FadeOut::create(infoFadeOutDuration),
                                       EaseBackIn::create(ScaleTo::create(infoFadeOutDuration + 0.2, 0)), NULL);
  
  layer->runAction(waitAndRemoveOverlay);
  infoSprite->runAction(Sequence::create(fadeInTurnInfo,
                                         DelayTime::create(infoDelayDuration),
                                         fadeOutTurnInfo, NULL));
}

void GameplayScene::_showActionDicesLayer() {
  auto controlsLayer = this->_getControlsLayer();
  
  auto actionDicesLayer = (ActionDiceLayer*) controlsLayer->getChildByName(ACTION_DICE_LAYER_NAME);
  auto playerSkillsLayer = (PlayerSkillsLayer*) controlsLayer->getChildByName(PLAYER_SKILL_LAYER_NAME);
  
  for (auto dice : actionDicesLayer->getDices()) {
    auto sprite = (ActionDiceSprite*) dice->getSprite();
    CC_SAFE_RETAIN(sprite);
    auto position = sprite->getParent()->getPosition();
    sprite->removeFromParent();
    
    auto spritePosition = sprite->getPosition();
    if (sprite->getOriginalPosition() != Vec2::ZERO) {
      spritePosition = sprite->getOriginalPosition();
    }
    
    auto newPosition = spritePosition + position;
    sprite->setPosition(newPosition);
    sprite->setScale(1);
    
    actionDicesLayer->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  actionDicesLayer->setVisible(Show::create());
  playerSkillsLayer->setVisible(false);
}

void GameplayScene::_showPlayerSkillsLayer() {
  auto controlsLayer = this->_getControlsLayer();
  
  auto actionDicesLayer = (ActionDiceLayer*) controlsLayer->getChildByName(ACTION_DICE_LAYER_NAME);
  auto playerSkillsLayer = (PlayerSkillsLayer*) controlsLayer->getChildByName(PLAYER_SKILL_LAYER_NAME);
  
  for (auto dice : actionDicesLayer->getDices()) {
    auto sprite = (ActionDiceSprite*) dice->getSprite();
    CC_SAFE_RETAIN(sprite);
    auto position = sprite->getParent()->getPosition();
    sprite->removeFromParent();
    
    auto newPosition = sprite->getPosition() + position;
    sprite->setPosition(newPosition);
    sprite->setOriginalPosition(newPosition);
    
    playerSkillsLayer->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  actionDicesLayer->setVisible(false);
  playerSkillsLayer->runAction(Show::create());
}

#pragma mark - Event Handlers

void GameplayScene::_handleActionDicesRolled(EventCustom* event) {
  this->_showPlayerSkillsLayer();
}

void GameplayScene::_handleTurnHasStarted(EventCustom* event) {
  log("turn has started");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    auto controlsLayer = this->_getControlsLayer();
    auto actionDiceLayer = (ActionDiceLayer*) controlsLayer->getChildByName(ACTION_DICE_LAYER_NAME);
    auto playerSkillsLayer = (PlayerSkillsLayer*) controlsLayer->getChildByName(PLAYER_SKILL_LAYER_NAME);
    
    Game::getInstance()->setFreeBootUsed(false);
    playerSkillsLayer->resetFreeBootUsed();
    playerSkillsLayer->resetDockableNodes();
    
    actionDiceLayer->resetRollCount();
    actionDiceLayer->resetActionDicesZIndex();
    
    auto show = Show::create();
    auto roll = CallFunc::create([&] {
      for (auto dice : Game::getInstance()->getActionDices()) {
        dice->roll();
      }
    });
    auto showAndRoll = Sequence::create(show, roll, NULL);
    
    controlsLayer->runAction(showAndRoll);
    
    this->_showActionDicesLayer();
    
    this->_showPlayerTurnInfo();
  } else if (IS(turn, DungeonTurn)) {
    this->_showDungeonTurnInfo();
    
    auto delay = DelayTime::create(TURN_INFO_DURATION);
    auto executeTurn = CallFunc::create([&] {
      Game::getInstance()->executeCurrentTurn();
    });
    this->runAction(Sequence::create(delay, executeTurn, NULL));
  }
}

void GameplayScene::_handleTurnHasEnded(EventCustom* event) {
  log("turn has ended");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    this->_getControlsLayer()->runAction(Hide::create());
  }
}
