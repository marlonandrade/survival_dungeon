//
//  ActionDiceStateNormal.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#include "ActionDiceStateNormal.h"

#include "Images.h"

#include "ActionDiceSprite.h"
#include "ActionDiceStateSelected.h"
#include "Dice.h"

USING_NS_CC;

#pragma mark - Public Interface

bool ActionDiceStateNormal::init() {
  return true;
}

bool ActionDiceStateNormal::canChangeState() {
  return true;
}

void ActionDiceStateNormal::changeState(Dice* dice) {
  auto sprite = dice->getSprite();
  
  auto selectedSprite = Sprite::create(IMG_DICE_ACTION_SELECTED);
  selectedSprite->setPosition(Vec2(sprite->getContentSize().width / 2,
                                   sprite->getContentSize().height / 2));
  sprite->addChild(selectedSprite);
  
  dice->setState(ActionDiceStateSelected::create());
}
