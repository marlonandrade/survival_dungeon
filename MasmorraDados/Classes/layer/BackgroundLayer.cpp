//
//  BackgroundLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 22/02/2015.
//
//

#include "BackgroundLayer.h"

#include "Definitions.h"

USING_NS_CC;

bool BackgroundLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  auto sprite = Sprite::create(IMG_BACKGROUND);
  Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
  sprite->getTexture()->setTexParameters(params);
  sprite->setPosition(Vec2(this->getContentSize().width / 2,
                           this->getContentSize().height / 2));
  sprite->setTextureRect(Rect(0, 0, 4000, 4000));
  
  this->addChild(sprite);
  
  return true;
}