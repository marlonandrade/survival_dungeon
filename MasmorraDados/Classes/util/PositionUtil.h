//
//  PositionUtil.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/17/15.
//
//

#ifndef __MasmorraDados__PositionUtil__
#define __MasmorraDados__PositionUtil__

#include "cocos2d.h"

class PositionUtil {
public:
  static cocos2d::Vec2 centerOfNode(cocos2d::Node* node);
  static cocos2d::Vec2 visibleCenter();
  static cocos2d::Vec2 positionForCoordinate(cocos2d::Vec2 coordinate);
  static cocos2d::Vec2 coordinateForPosition(cocos2d::Vec2 position);
};

#endif /* defined(__MasmorraDados__PositionUtil__) */
