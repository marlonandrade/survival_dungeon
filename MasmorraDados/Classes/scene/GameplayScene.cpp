//
//  GameplayScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "GameplayScene.h"

#include "Events.h"
#include "NodeNames.h"

#include "PlayerTurnLayer.h"
#include "TurnChangeLayer.h"
#include "ScrollableDungeonLayer.h"

#include "DungeonTurn.h"
#include "PlayerTurn.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameplayScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->_setupChildren();
  this->_setupEventHandlers();
  
  Game::getInstance()->setupCharacterInitialCoordinate();
  
  return true;
}

#pragma mark - Private Interface

void GameplayScene::_setupChildren() {
  this->addChild(ScrollableDungeonLayer::create(), 0);
  this->addChild(PlayerTurnLayer::create(), 1);
  this->addChild(TurnChangeLayer::create(), 2);
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

PlayerTurnLayer* GameplayScene::_getPlayerTurnLayer() {
  return (PlayerTurnLayer*) this->getChildByName(PLAYER_TURN_LAYER);
}

TurnChangeLayer* GameplayScene::_getTurnChangeLayer() {
  return (TurnChangeLayer*) this->getChildByName(TURN_CHANGE_LAYER_NAME);
}

#pragma mark - Event Handlers

void GameplayScene::_handleActionDicesRolled(EventCustom* event) {
  this->_getPlayerTurnLayer()->showGameplayLayer();
}

void GameplayScene::_handleTurnHasStarted(EventCustom* event) {
  log("turn has started");
  
  auto turn = (Turn*) event->getUserData();
  
  if (IS(turn, PlayerTurn)) {
    Game::getInstance()->resetForPlayerTurn();
    
    this->_getPlayerTurnLayer()->playerTurnHasStarted();
    this->_getTurnChangeLayer()->showPlayerTurnInfo();
  } else if (IS(turn, DungeonTurn)) {
    this->_getTurnChangeLayer()->showDungeonTurnInfo();
    
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
    this->_getPlayerTurnLayer()->runAction(Hide::create());
  }
}
