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
  
  this->_setupActionDices(dices);
  
  return true;
}

#pragma mark - Private Interface

void ActionDiceLayer::_setupActionDices(Vector<ActionDice*> dices) {
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
  
  auto x = this->getContentSize().width / 2 - totalWidth / 2;
  auto y = ACTION_DICE_BACKGROUND_BOTTOM_MARGIN;
  
  backgroundLayer->setContentSize(Size(totalWidth, totalHeight));
  backgroundLayer->setPosition(Vec2(x, y));
  
  this->addChild(backgroundLayer);
}