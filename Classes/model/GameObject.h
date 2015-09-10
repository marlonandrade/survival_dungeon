//
//  GameObject.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __SurvivalDungeon__GameObject__
#define __SurvivalDungeon__GameObject__

#include "cocos2d.h"

class GameObject : public cocos2d::Ref {
public:
  virtual bool init();
  CREATE_FUNC(GameObject);
};

#endif /* defined(__SurvivalDungeon__GameObject__) */
