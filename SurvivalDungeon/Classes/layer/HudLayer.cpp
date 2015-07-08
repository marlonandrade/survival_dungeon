//
//  HudLayer.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/24/15.
//
//

#include "HudLayer.h"

#include "Definitions.h"
#include "NodeNames.h"

USING_NS_CC;

#pragma mark - Public Interface

bool HudLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->setName(HUD_LAYER_NAME);
  this->_setupChildren();
  
  return true;
}

void HudLayer::adjustLevel(int level) {
  this->_getLevelLabel()->setString(this->_append(HUD_LEVEL_STRING, level));
}

void HudLayer::adjustXp(int xp) {
  this->_getXpLabel()->setString(this->_append(HUD_XP_STRING, xp));
}

void HudLayer::adjustCoins(int coins) {
  this->_getCoinsLabel()->setString(this->_append(HUD_COINS_STRING, coins));
}

#pragma mark - Private Interface

void HudLayer::_setupChildren() {
  auto padding = 12;
  
  auto x = 40;
  auto y = this->getContentSize().height - padding;
  
  auto initialLevel = this->_append(HUD_LEVEL_STRING, 0);
  auto levelLabel = Label::createWithTTF(initialLevel, HUD_FONT_NAME, HUD_FONT_SIZE);
  levelLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  levelLabel->setName(HUD_LEVEL_LABEL_NAME);
  levelLabel->setPosition(Vec2(x, y));
  this->addChild(levelLabel);
  
  y = levelLabel->getPosition().y - levelLabel->getContentSize().height;
  
  auto initialXp = this->_append(HUD_XP_STRING, INITIAL_EXPERIENCE);
  auto xpLabel = Label::createWithTTF(initialXp, HUD_FONT_NAME, HUD_FONT_SIZE);
  xpLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  xpLabel->setName(HUD_XP_LABEL_NAME);
  xpLabel->setPosition(Vec2(x, y));
  this->addChild(xpLabel);
  
  y = xpLabel->getPosition().y - xpLabel->getContentSize().height;
  
  auto initialCoins = this->_append(HUD_COINS_STRING, INITIAL_COINS);
  auto coinsLabel = Label::createWithTTF(initialCoins, HUD_FONT_NAME, HUD_FONT_SIZE);
  coinsLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
  coinsLabel->setName(HUD_COINS_LABEL_NAME);
  coinsLabel->setPosition(Vec2(x, y));
  this->addChild(coinsLabel);
}

Label* HudLayer::_getLevelLabel() {
  return this->getChildByName<Label*>(HUD_LEVEL_LABEL_NAME);
}

Label* HudLayer::_getXpLabel() {
  return this->getChildByName<Label*>(HUD_XP_LABEL_NAME);
}

Label* HudLayer::_getCoinsLabel() {
  return this->getChildByName<Label*>(HUD_COINS_LABEL_NAME);
}

std::string HudLayer::_append(std::string base, int number) {
  std::stringstream ss;
  ss << base;
  ss << " ";
  ss << number;
  return ss.str();
}
