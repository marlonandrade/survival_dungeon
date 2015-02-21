//
//  Skill.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Skill__
#define __MasmorraDados__Skill__

#include "GameObject.h"

class Skill : public GameObject {
public:
  static Skill* createWithValueMap(cocos2d::ValueMap map);
  bool initWithValueMap(cocos2d::ValueMap map);
  
  CC_SYNTHESIZE(std::string, cost, Cost);
  CC_SYNTHESIZE(std::string, effect, Effect);
};

#endif /* defined(__MasmorraDados__Skill__) */
