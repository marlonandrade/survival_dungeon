//
//  Character.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Character__
#define __MasmorraDados__Character__

#include "GameObject.h"

class Skill;

class Character : public GameObject {
  CC_SYNTHESIZE(std::string, _name, Name);
  CC_SYNTHESIZE(std::string, _imagePath, ImagePath);
  CC_SYNTHESIZE(std::string, _classType, ClassType);
  CC_SYNTHESIZE(Skill*, _initialSkill, InitialSkill);
  
public:
  static Character* createWithValueMap(cocos2d::ValueMap map);
  virtual bool initWithValueMap(cocos2d::ValueMap map);
};

#endif /* defined(__MasmorraDados__Character__) */
