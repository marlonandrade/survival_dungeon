//
//  DiceFace.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#include "DiceFace.h"

USING_NS_CC;

#pragma mark - Public Interface

DiceFace* DiceFace::createWithImagePath(std::string imagePath) {
  auto face = new (std::nothrow) DiceFace();
  if (face && face->initWithImagePath(imagePath)) {
    face->autorelease();
  } else {
    CC_SAFE_DELETE(face);
  }
  return face;
}

bool DiceFace::initWithImagePath(std::string imagePath) {
  if (!GameObject::init()) {
    return false;
  }
  
  this->setImagePath(imagePath);
  
  return true;
}