//
//  FileUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#include "FileUtil.h"

#include "Images.h"

USING_NS_CC;

#pragma mark - Public Interface

static FileUtil *_fileUtil = nullptr;

FileUtil* FileUtil::getInstance() {
  if (!_fileUtil) {
    _fileUtil = new (std::nothrow) FileUtil();
    _fileUtil->init();
  }
  
  return _fileUtil;
}

std::string FileUtil::characterFileName(int hitPoints) {
  return this->fileNameForBaseImage(IMG_DICE_CHAR, hitPoints);
}

std::string FileUtil::damageTakenFileName(int damage) {
  return this->fileNameForBaseImage(IMG_DAMAGE_TAKEN, damage);
}

std::string FileUtil::damageDealtFileName(int damage) {
  return this->fileNameForBaseImage(IMG_DAMAGE_DEALT, damage);
}

std::string FileUtil::fileNameForBaseImage(std::string baseName, int amount) {
  auto xxPos = baseName.find("xx");
  
  std::stringstream stream;
  stream << amount;
  auto value = stream.str();
  
  return baseName.replace(xxPos, 2, value);
}

Sprite* FileUtil::damageTakenSprite(int damage) {
  auto sprite = _damageTakenSprites.at(damage);
  
  if (!sprite) {
    sprite = Sprite::create(this->damageTakenFileName(damage));
    _damageTakenSprites.insert(damage, sprite);
  }
  
  return sprite;
}

Sprite* FileUtil::damageDealtSprite(int damage) {
  auto sprite = _damageDealtSprites.at(damage);
  
  if (!sprite) {
    sprite = Sprite::create(this->damageDealtFileName(damage));
    _damageDealtSprites.insert(damage, sprite);
  }
  
  return sprite;
}