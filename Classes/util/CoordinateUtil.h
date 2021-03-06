//
//  CoordinateUtil.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 5/16/15.
//
//

#ifndef __SurvivalDungeon__CoordinateUtil__
#define __SurvivalDungeon__CoordinateUtil__

#include "cocos2d.h"

class CoordinateUtil {
public:
  static std::string nameForCoordinate(cocos2d::Vec2 coordinate);
  
  static int indexForCoordinate(cocos2d::Vec2 coordinate);
  static cocos2d::Vec2 coordinateForIndex(int index);
  
  static std::vector<cocos2d::Vec2> adjacentCoordinatesTo(cocos2d::Vec2 coordinate);
};

#endif /* defined(__SurvivalDungeon__CoordinateUtil__) */
