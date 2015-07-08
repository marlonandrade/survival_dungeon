//
//  DiceDragHandlerFactory.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/18/15.
//
//

#ifndef __SurvivalDungeon__DiceDragHandlerFactory__
#define __SurvivalDungeon__DiceDragHandlerFactory__

#include "cocos2d.h"

class CommonDiceDragHandler;
class Dice;

class DiceDragHandlerFactory : public cocos2d::Ref {
public:
  static CommonDiceDragHandler* getHandler(Dice* dice);
};

#endif /* defined(__SurvivalDungeon__DiceDragHandlerFactory__) */
