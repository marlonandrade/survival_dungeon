//
//  Skill.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __SurvivalDungeon__Skill__
#define __SurvivalDungeon__Skill__

#include "GameObject.h"

class Skill : public GameObject {
  CC_SYNTHESIZE(std::string, _cost, Cost);
  CC_SYNTHESIZE(std::string, _effect, Effect);
  
public:
  static Skill* createWithValueMap(cocos2d::ValueMap map);
  bool initWithValueMap(cocos2d::ValueMap map);
};

#endif /* defined(__SurvivalDungeon__Skill__) */
