//
//  FileUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#include "FileUtil.h"

#include "Images.h"

#pragma mark - Public Interface

std::string FileUtil::characterFileName(int hitPoints) {
  return FileUtil::fileNameForBaseImage(IMG_DICE_CHAR, hitPoints);
}

std::string FileUtil::damageFileName(int damage) {
  return FileUtil::fileNameForBaseImage(IMG_DAMAGE_TAKEN, damage);
}

std::string FileUtil::fileNameForBaseImage(std::string baseName, int amount) {
  auto xxPos = baseName.find("xx");
  
  std::stringstream stream;
  stream << amount;
  auto value = stream.str();
  
  return baseName.replace(xxPos, 2, value);
}
