//
//  Dungeon.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dungeon.h"

bool Dungeon::init() {
  if (!GameObject::init()) {
    return false;
  }
  
  return true;
}