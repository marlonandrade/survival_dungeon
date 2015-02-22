//
//  ExitLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "ExitLayer.h"

USING_NS_CC;

bool ExitLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  return true;
}

#pragma mark - Public Interface

void ExitLayer::leave() {
}

#pragma mark - Entering/Exiting 'stage'

void ExitLayer::onEnter() {
  Layer::onEnter();
  
  auto keyboardListener = EventListenerKeyboard::create();
  keyboardListener->onKeyReleased = CC_CALLBACK_2(ExitLayer::onKeyReleased, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void ExitLayer::onExit() {
  _eventDispatcher->removeEventListenersForTarget(this);
  
  Layer::onExit();
}

#pragma mark - Keyboard Callback

void ExitLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
                         cocos2d::Event *event) {
  if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
      keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
    this->leave();
  }
}