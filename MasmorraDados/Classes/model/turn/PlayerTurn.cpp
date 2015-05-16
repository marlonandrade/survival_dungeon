//
//  PlayerTurn.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#include "PlayerTurn.h"

#include "Events.h"

#include "DungeonTurn.h"
#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool PlayerTurn::init() {
  if (!Turn::init()) {
    return false;
  }
  
  this->_actionDicesRolled = false;
  this->_setupEventHandlers();
  
  return true;
}

bool PlayerTurn::isActionDicesRolled() {
  return _actionDicesRolled;
}

void PlayerTurn::finish(Game *game) {
  game->restoreFreeBoot();
  game->setTurn(DungeonTurn::create());
}

#pragma mark - Private Interface

void PlayerTurn::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto actionDicesRolledCallback = CC_CALLBACK_1(PlayerTurn::_handleActionDicesRolled, this);
  this->setActionDicesRolledListener(
    dispatcher->addCustomEventListener(EVT_ACTION_DICES_ROLLED, actionDicesRolledCallback)
  );
}

#pragma mark - Event Handlers

void PlayerTurn::_handleActionDicesRolled(EventCustom *event) {
  this->_actionDicesRolled = true;
}