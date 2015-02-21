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
public:
  static Character* createWithValueMap(cocos2d::ValueMap map);
  bool initWithValueMap(cocos2d::ValueMap map);
  
  CC_SYNTHESIZE(std::string, name, Name);
  CC_SYNTHESIZE(std::string, imagePath, ImagePath);
  CC_SYNTHESIZE(std::string, classType, ClassType);
  CC_SYNTHESIZE(Skill*, initialSkill, InitialSkill);
};

#endif /* defined(__MasmorraDados__Character__) */
