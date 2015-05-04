//
//  RuneRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#include "RuneRoom.h"

#include "Images.h"

void RuneRoom::initialize() {
}

std::string RuneRoom::getImagePath() {
  return IMG_ROOM_RUNE;
}

bool RuneRoom::isExplorable() {
  return true;
}