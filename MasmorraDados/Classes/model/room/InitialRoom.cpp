//
//  InitialRoom.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#include "InitialRoom.h"

#include "Images.h"

void InitialRoom::initialize() {
}

std::string InitialRoom::getImagePath() {
  return IMG_ROOM_INITIAL;
}

bool InitialRoom::isExplorable() {
  return true;
}