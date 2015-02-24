//
//  BackgroundLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 22/02/2015.
//
//

#include "BackgroundLayer.h"

USING_NS_CC;

bool BackgroundLayer::init() {
  if (!Layer::init()) {
    return false;
  }
  
  this->addChild(Sprite::create("images/background.jpg"));
  
  return true;
}