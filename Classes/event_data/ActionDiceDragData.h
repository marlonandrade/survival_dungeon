//
//  ActionDiceDragData.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#ifndef __SurvivalDungeon__ActionDiceDragData__
#define __SurvivalDungeon__ActionDiceDragData__

#include "GameObject.h"

#include "ActionDiceSprite.h"

class ActionDiceDragData : public GameObject {
  CC_SYNTHESIZE_RETAIN(ActionDiceSprite*, _sprite, Sprite);
  CC_SYNTHESIZE_RETAIN(cocos2d::Touch*, _touch, Touch);
public:
  CREATE_FUNC(ActionDiceDragData);
  
};

#endif /* defined(__SurvivalDungeon__ActionDiceDragData__) */
