//
//  DiceSelectLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#include "DiceSelectLayer.h"

#include "Definitions.h"
#include "Events.h"
#include "Images.h"
#include "NodeNames.h"

#include "ActionDiceSprite.h"

#include "ActionDiceStateNormal.h"
#include "ActionDiceStateSelected.h"

#include "Game.h"

USING_NS_CC;

#pragma mark - Public Interface

bool DiceSelectLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(PLAYER_TURN_DICE_SELECT_LAYER);
  
  auto dices = Game::getInstance()->getActionDices();
  this->setDices(dices);
  this->_setupChilds(dices);
  this->resetRollCount();
  this->_setupEventHandlers();
  
  return true;
}

void DiceSelectLayer::showDices() {
  for (auto dice : Game::getInstance()->getActionDices()) {
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
    
    this->addChild(sprite);
    CC_SAFE_RELEASE(sprite);
  }
  
  this->runAction(Show::create());
}

void DiceSelectLayer::resetRollCount() {
  this->_rollCount = 1;
  this->_adjustRerollButtonTextures();
}

void DiceSelectLayer::resetActionDicesZIndex() {
  for (auto dice : this->getDices()) {
    auto sprite = dice->getSprite();
    sprite->setLocalZOrder(ACTION_DICE_Z_ORDER);
  }
}

#pragma mark - Private Interface

void DiceSelectLayer::_setupChilds(Vector<ActionDice *> dices) {
  auto backgroundLayer = LayerColor::create(Color4B(0, 0, 0, 100));
  
  auto diceSprite = dices.at(0)->getSprite();
  
  auto width = this->getContentSize().width;
  auto height = diceSprite->getContentSize().height + ACTION_DICE_MARGIN * 2;
  backgroundLayer->setContentSize(Size(width, height));
  
  this->addChild(backgroundLayer);
  
  auto actionDices = this->_createActionDices(dices);
  this->addChild(actionDices);
  auto dicesX = backgroundLayer->getContentSize().width / 2 -
                actionDices->getContentSize().width / 2;
  auto dicesY = ACTION_DICE_MARGIN;
  actionDices->setPosition(Vec2(dicesX, dicesY));
  
  auto rerollButton = this->_createRerollButton();
  this->addChild(rerollButton);
  auto rerollX = actionDices->getPosition().x / 2;
  auto rerollY = height / 2;
  rerollButton->setPosition(Vec2(rerollX, rerollY));
  
  auto okButton = this->_createOkButton();
  this->addChild(okButton);
  auto okX = width - (actionDices->getPosition().x / 2);
  auto okY = height / 2;
  okButton->setPosition(Vec2(okX, okY));
  
  this->resetActionDicesZIndex();
}

Node* DiceSelectLayer::_createActionDices(Vector<ActionDice*> dices) {
  auto actionDices = Node::create();
  
  auto marginPerDice = ACTION_DICE_MARGIN_PER_DICE;
  
  auto diceSprite = dices.at(0)->getSprite();
  
  int numberOfDices = dices.size();
  for (int i = 0; i < numberOfDices; i++) {
    diceSprite = dices.at(i)->getSprite();
    
    auto width = diceSprite->getContentSize().width;
    auto height = diceSprite->getContentSize().height;
    
    auto x = width * i + marginPerDice * i + width / 2;
    auto y = height / 2;
    
    diceSprite->setPosition(Vec2(x, y));
    actionDices->addChild(diceSprite, i);
  }
  
  auto totalWidth = diceSprite->getContentSize().width * numberOfDices +
                    marginPerDice * (numberOfDices - 1);
  auto totalHeight = diceSprite->getContentSize().height;
  
  actionDices->setContentSize(Size(totalWidth, totalHeight));
  
  return actionDices;
}

Node* DiceSelectLayer::_createRerollButton() {
  auto rerollButton = ui::Button::create();
  rerollButton->setName(DICE_REROLL_BUTTON_NAME);
  rerollButton->addTouchEventListener(CC_CALLBACK_2(DiceSelectLayer::_handleRerollTouched, this));
  
  return rerollButton;
}

Node* DiceSelectLayer::_createOkButton() {
  auto okButton = ui::Button::create(IMG_BUTTON_OK_NORMAL,
                                     IMG_BUTTON_OK_SELECTED,
                                     IMG_BUTTON_OK_DISABLED);
  okButton->setName(DICE_OK_BUTTON_NAME);
  okButton->addTouchEventListener(CC_CALLBACK_2(DiceSelectLayer::_handleOkTouched, this));
  
  return okButton;
}

void DiceSelectLayer::_setupEventHandlers() {
  auto dispatcher = Director::getInstance()->getEventDispatcher();
  
  auto diceStateNewCallback = CC_CALLBACK_1(DiceSelectLayer::_handleDiceStateNew, this);
  this->setDiceStateNewListener(
    dispatcher->addCustomEventListener(EVT_DICE_STATE_NEW, diceStateNewCallback)
  );
}

void DiceSelectLayer::_setRerollButtonEnabled(bool enabled) {
  if (this->_rollCount > 3) {
    enabled = false;
  }
  
  auto rerollButton = this->_getRerollButton();
  rerollButton->setEnabled(enabled);
  rerollButton->setBright(enabled);
}

void DiceSelectLayer::_adjustRerollButtonTextures() {
  auto rerollButton = this->_getRerollButton();
  
  std::string normalTexture = IMG_BUTTON_REROLL_NORMAL;
  std::string selectedTexture = IMG_BUTTON_REROLL_SELECTED;
  std::string disabledTexture = IMG_BUTTON_REROLL_DISABLED;
  
  auto normalXXPos = normalTexture.find("xx");
  auto selectedXXPos = selectedTexture.find("xx");
  auto disabledXXPos = disabledTexture.find("xx");
  
  std::stringstream stream;
  stream << 4 - this->_rollCount;
  auto rerollsLeft = stream.str();
  
  normalTexture = normalTexture.replace(normalXXPos, 1, rerollsLeft);
  selectedTexture = selectedTexture.replace(selectedXXPos, 1, rerollsLeft);
  disabledTexture = disabledTexture.replace(disabledXXPos, 1, rerollsLeft);
  
  rerollButton->loadTextures(normalTexture, selectedTexture);
  rerollButton->loadTextureDisabled(disabledTexture);
}

ui::Button* DiceSelectLayer::_getRerollButton() {
  return (ui::Button*) this->getChildByName(DICE_REROLL_BUTTON_NAME);
}

#pragma mark - Event Handlers

void DiceSelectLayer::_handleRerollTouched(Ref* sender, ui::Widget::TouchEventType type) {
  if (type == ui::Widget::TouchEventType::ENDED) {
    this->_rollCount++;
    
    this->_adjustRerollButtonTextures();
    
    for (auto dice : this->getDices()) {
      if (dice->isSelected()) {
        dice->roll();
      } else if (!dice->isDisabled()) {
        dice->setDisabled();
      }
    }
  }
}

void DiceSelectLayer::_handleOkTouched(Ref* sender, ui::Widget::TouchEventType type) {
  for (auto dice : this->getDices()) {
    dice->setRolled();
  }
  
  if (type == ui::Widget::TouchEventType::ENDED) {
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchCustomEvent(EVT_ACTION_DICES_ROLLED, this);
  }
}

void DiceSelectLayer::_handleDiceStateNew(EventCustom* event) {
  bool anyDiceSelected = false;
  for (auto dice : this->getDices()) {
    if (dice->isSelected()) {
      anyDiceSelected = true;
      break;
    }
  }
  
  this->_setRerollButtonEnabled(anyDiceSelected);
}
