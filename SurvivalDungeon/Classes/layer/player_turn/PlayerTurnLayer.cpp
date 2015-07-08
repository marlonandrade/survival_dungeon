//
//  PlayerTurnLayer.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#include "PlayerTurnLayer.h"

#include "DiceSelectLayer.h"
#include "GameplayLayer.h"

#include "NodeNames.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool PlayerTurnLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setVisible(false);
  this->setName(PLAYER_TURN_LAYER);
  
  this->_setupChildren();
  
  return true;
}

void PlayerTurnLayer::playerTurnHasStarted() {
  auto diceSelectLayer = this->_getDiceSelectLayer();
  auto gameplayLayer = this->_getGameplayLayer();
  
  gameplayLayer->resetFreeBootUsed();
  gameplayLayer->resetDockableNodes();
  
  diceSelectLayer->resetRollCount();
  diceSelectLayer->resetActionDicesZIndex();
  
  auto show = Show::create();
  auto roll = CallFunc::create([&] {
    for (auto dice : Game::getInstance()->getActionDices()) {
      dice->roll();
    }
  });
  auto showAndRoll = Sequence::create(show, roll, NULL);
  
  this->runAction(showAndRoll);
  
  this->showDiceSelectLayer();
}

void PlayerTurnLayer::showDiceSelectLayer() {
  this->_getDiceSelectLayer()->showDices();
  this->_getGameplayLayer()->setVisible(false);
}

void PlayerTurnLayer::showGameplayLayer() {
  this->_getDiceSelectLayer()->setVisible(false);
  this->_getGameplayLayer()->migrateDicesAndShow();
}

#pragma mark - Private Interface

DiceSelectLayer* PlayerTurnLayer::_getDiceSelectLayer() {
  return (DiceSelectLayer*) this->getChildByName(PLAYER_TURN_DICE_SELECT_LAYER);
}

GameplayLayer* PlayerTurnLayer::_getGameplayLayer() {
  return (GameplayLayer*) this->getChildByName(PLAYER_TURN_GAMEPLAY_LAYER);
}

void PlayerTurnLayer::_setupChildren() {
  this->addChild(DiceSelectLayer::create());
  this->addChild(GameplayLayer::create());
}
