//
//  ActionDiceLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#include "ActionDiceLayer.h"

#include "Definitions.h"

USING_NS_CC;

#pragma mark - Public Interface

ActionDiceLayer* ActionDiceLayer::createWithDices(Vector<ActionDice *> dices) {
  auto layer = new (std::nothrow) ActionDiceLayer();
  if (layer && layer->initWithDices(dices)) {
    layer->autorelease();
  } else {
    CC_SAFE_DELETE(layer);
  }
  return layer;
}

bool ActionDiceLayer::initWithDices(Vector<ActionDice *> dices) {
  if (!Layer::init()) {
    return false;
  }
  
  this->setDices(dices);
  
  auto actionDices = this->_createActionDices(dices);
  auto rerollButton = this->_createRerollButton();
  auto okButton = this->_createOkButton();
  
  this->addChild(actionDices);
  this->addChild(rerollButton);
  this->addChild(okButton);
  
  auto x = this->getContentSize().width / 2 - actionDices->getContentSize().width / 2;
  auto y = ACTION_DICE_BACKGROUND_BOTTOM_MARGIN;
  
  actionDices->setPosition(Vec2(x, y));
  
  x = actionDices->getPosition().x + actionDices->getContentSize().width + ACTION_DICE_BACKGROUND_BUTTON_MARGIN;
  y = actionDices->getPosition().y + actionDices->getContentSize().height - rerollButton->getContentSize().height - 10;
  
  rerollButton->setPosition(Vec2(x, y));
  
  y = actionDices->getPosition().y + 10;
  
  okButton->setPosition(Vec2(x, y));
  
  return true;
}

#pragma mark - Private Interface

Node* ActionDiceLayer::_createActionDices(Vector<ActionDice*> dices) {
  auto backgroundLayer = LayerColor::create(Color4B(0, 0, 0, 100));
  
  auto margin = ACTION_DICE_MARGIN;
  auto marginPerDice = ACTION_DICE_MARGIN_PER_DICE;
  
  auto diceSprite = dices.at(0)->getSprite();
  
  int numberOfDices = dices.size();
  for (int i = 0; i < numberOfDices; i++) {
    diceSprite = dices.at(i)->getSprite();
    
    auto width = diceSprite->getContentSize().width;
    auto height = diceSprite->getContentSize().height;
    
    auto x = width * i + marginPerDice * i + width / 2 + margin;
    auto y = height / 2 + margin;
    
    diceSprite->setPosition(Vec2(x, y));
    backgroundLayer->addChild(diceSprite, i);
  }
  
  auto totalHorizontalMargin = margin * 2 + marginPerDice * (numberOfDices - 1);
  auto totalVerticalMargin = margin * 2;
  
  auto totalWidth = numberOfDices * diceSprite->getContentSize().width + totalHorizontalMargin;
  auto totalHeight = diceSprite->getContentSize().height + totalVerticalMargin;
  
  backgroundLayer->setContentSize(Size(totalWidth, totalHeight));
  
  return backgroundLayer;
}

Node* ActionDiceLayer::_createRerollButton() {
  auto rerollButton = ui::Button::create("images/button/normal.png",
                                         "images/button/selected.png",
                                         "images/button/disabled.png");
  rerollButton->setTitleText("reroll");
  rerollButton->setTitleColor(Color3B::BLACK);
  rerollButton->setAnchorPoint(Vec2(0, 0));
  rerollButton->setCapInsets(Rect(2, 2, 42, 32));
  rerollButton->setScale9Enabled(true);
  rerollButton->setContentSize(Size(40, 20));
  rerollButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      for (auto dice : this->getDices()) {
        if (dice->isSelected()) {
          dice->roll();
        } else if (!dice->isDisabled()) {
          dice->setDisabled();
        }
      }
      log("reroll pressed");
    }
  });
  
  return rerollButton;
}

Node* ActionDiceLayer::_createOkButton() {
  auto okButton = ui::Button::create("images/button/normal.png",
                                     "images/button/selected.png",
                                     "images/button/disabled.png");
  okButton->setTitleText("ok");
  okButton->setTitleColor(Color3B::BLACK);
  okButton->setAnchorPoint(Vec2(0, 0));
  okButton->setCapInsets(Rect(2, 2, 42, 32));
  okButton->setScale9Enabled(true);
  okButton->setContentSize(Size(40, 20));
  okButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
    if (type == ui::Widget::TouchEventType::ENDED) {
      log("ok pressed");
    }
  });
  
  return okButton;
}