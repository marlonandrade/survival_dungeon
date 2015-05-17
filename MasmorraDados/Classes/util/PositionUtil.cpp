//
//  PositionUtil.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#include "PositionUtil.h"

#include "Definitions.h"

USING_NS_CC;

Vec2 PositionUtil::centerOfNode(Node* node) {
  auto halfSize = node->getContentSize() / 2;
  return Vec2(halfSize.width, halfSize.height);
}

Vec2 PositionUtil::visibleCenter() {
  Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
  Size visibleSize = Director::getInstance()->getVisibleSize();
  
  return Vec2(visibleSize.width / 2 + visibleOrigin.x,
              visibleSize.height / 2 + visibleOrigin.y);
}

Vec2 PositionUtil::positionForCoordinate(Vec2 coordinate) {
  auto centerCoordinate = INITIAL_COORDINATE;
  auto visibleCenter = PositionUtil::visibleCenter();
  
  auto offsetX = coordinate.x - centerCoordinate.x;
  auto offsetY = coordinate.y - centerCoordinate.y;
  
  return Vec2(visibleCenter.x + offsetX * TILE_DIMENSION,
              visibleCenter.y + offsetY * TILE_DIMENSION);
}

Vec2 PositionUtil::coordinateForPosition(Vec2 position) {
  auto centerCoordinate = INITIAL_COORDINATE;
  auto visibleCenter = PositionUtil::visibleCenter();
  
  auto offsetX = position.x - visibleCenter.x;
  auto offsetY = position.y - visibleCenter.y;
  
  auto halfTileDimension = TILE_DIMENSION / 2;
  
  offsetX > halfTileDimension ? offsetX += halfTileDimension : offsetX -= halfTileDimension;
  offsetY > halfTileDimension ? offsetY += halfTileDimension : offsetY -= halfTileDimension;
  
  return Vec2(centerCoordinate.x + int(offsetX / TILE_DIMENSION),
              centerCoordinate.y + int(offsetY / TILE_DIMENSION));
}