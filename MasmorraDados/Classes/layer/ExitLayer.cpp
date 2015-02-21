//
//  ExitLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "ExitLayer.h"

USING_NS_CC;

bool Exit::init() {
  if (!Layer::init()) {
    return false;
  }
  
  return true;
}

#pragma mark - Public Interface

void Exit::leave() {
}

#pragma mark - Entering/Exiting 'stage'

void Exit::onEnter() {
  Layer::onEnter();
  
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyReleased = CC_CALLBACK_2(Exit::onKeyReleased, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Exit::onExit() {
  _eventDispatcher->removeEventListenersForTarget(this);
  
  Layer::onExit();
}

#pragma mark - Keyboard Callback

void Exit::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
                         cocos2d::Event *event) {
  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
      keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
    this->leave();
  }
}