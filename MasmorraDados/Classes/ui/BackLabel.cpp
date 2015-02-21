//
//  BackLabel.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "BackLabel.h"
#include "Definitions.h"

USING_NS_CC;

cocos2d::Label* BackLabel::create() {
  Size visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  
  float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
  
  TTFConfig labelConfig;
  labelConfig.fontFilePath = "fonts/farcry.ttf";
  labelConfig.fontSize = 25 * scaleFactor;
  
  return Label::createWithTTF(labelConfig, "VOLTAR");
}