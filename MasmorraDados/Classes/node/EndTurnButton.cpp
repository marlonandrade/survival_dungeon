//
//  EndTurnButton.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#include "EndTurnButton.h"

#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

USING_NS_CC;

#pragma mark - Public Interface

bool EndTurnButton::init() {
  if (!ui::Button::init(IMG_BUTTON_END_TURN_NORMAL,
                        IMG_BUTTON_END_TURN_SELECTED,
                        IMG_BUTTON_END_TURN_DISABLED)) {
    return false;
  }
  
  this->setName(END_TURN_BUTTON_NAME);
  this->addTouchEventListener(CC_CALLBACK_2(EndTurnButton::_handleButtonTouched, this));
  
  return true;
}

#pragma mark - Private Interface

void EndTurnButton::_handleButtonTouched(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_END_PLAYER_TURN, this);
  }
}