//
//  CoordinateUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/16/15.
//
//

#include "CoordinateUtil.h"

#include "Definitions.h"

USING_NS_CC;

std::string CoordinateUtil::nameForCoordinate(Vec2 coordinate) {
  std::stringstream ss;
  ss << CoordinateUtil::indexForCoordinate(coordinate);
  return ss.str();
}

int CoordinateUtil::indexForCoordinate(Vec2 coordinate) {
  return coordinate.x * DUNGEON_SIZE + coordinate.y;
}

Vec2 CoordinateUtil::coordinateForIndex(int index) {
  auto x = index / DUNGEON_SIZE;
  auto y = index % DUNGEON_SIZE;
  return Vec2(x, y);
}