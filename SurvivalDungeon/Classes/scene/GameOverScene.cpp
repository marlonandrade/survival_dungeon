//
//  GameOverScene.cpp
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 7/2/15.
//
//

#include "GameOverScene.h"

#include "Definitions.h"
#include "NodeNames.h"

#include "PositionUtil.h"

USING_NS_CC;

#pragma mark - Public Interface

bool GameOverScene::init() {
  if (!Scene::init()) {
    return false;
  }
  
  this->_setupChildren();
  
  return true;
}

#pragma mark - Private Interface

void GameOverScene::_setupChildren() {
  auto layer = Layer::create();
  
  auto center = PositionUtil::visibleCenter();
  
  auto gameOverLabel = Label::createWithTTF("Game Over",
                                            GAME_OVER_FONT_NAME,
                                            GAME_OVER_FONT_SIZE);
  gameOverLabel->setName(GAME_OVER_LABEL_NAME);
  gameOverLabel->setPosition(center);
  layer->addChild(gameOverLabel);
  
  this->addChild(layer);
}
