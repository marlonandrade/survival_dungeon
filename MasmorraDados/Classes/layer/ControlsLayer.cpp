//
//  ControlsLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#include "ControlsLayer.h"

#include "ActionDiceLayer.h"
#include "PlayerSkillsLayer.h"

#include "NodeNames.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ControlsLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setVisible(false);
  this->setName(CONTROLS_LAYER_NAME);
  
  this->_setupChildren();
  this->_setupEventHandlers();
  
  return true;
}

void ControlsLayer::playerTurnHasStarted() {
  auto actionDiceLayer = this->_getActionDiceLayer();
  auto playerSkillsLayer = this->_getPlayerSkillsLayer();
  
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
  
  this->runAction(showAndRoll);
  
  this->showActionDices();
}

void ControlsLayer::showActionDices() {
  this->_getActionDiceLayer()->showDices();
  this->_getPlayerSkillsLayer()->setVisible(false);
}

void ControlsLayer::showPlayerSkillsLayer() {
  this->_getActionDiceLayer()->setVisible(false);
  this->_getPlayerSkillsLayer()->migrateDicesAndShow();
}

#pragma mark - Private Interface

ActionDiceLayer* ControlsLayer::_getActionDiceLayer() {
  return (ActionDiceLayer*) this->getChildByName(ACTION_DICE_LAYER_NAME);
}

PlayerSkillsLayer* ControlsLayer::_getPlayerSkillsLayer() {
  return (PlayerSkillsLayer*) this->getChildByName(PLAYER_SKILL_LAYER_NAME);
}

void ControlsLayer::_setupChildren() {
  this->addChild(ActionDiceLayer::create());
  this->addChild(PlayerSkillsLayer::create());
}

void ControlsLayer::_setupEventHandlers() {
  // TODO: implementar
}