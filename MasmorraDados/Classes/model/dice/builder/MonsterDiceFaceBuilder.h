//
//  MonsterDiceFaceBuilder.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__MonsterDiceFaceBuilder__
#define __MasmorraDados__MonsterDiceFaceBuilder__

#include "DiceFaceBuilder.h"

class Monster;

class MonsterDiceFaceBuilder : public DiceFaceBuilder {
public:
  CREATE_FUNC(MonsterDiceFaceBuilder);
  virtual DiceFace* diceFace(cocos2d::ValueMap &map);
private:
  Monster* monsterFrom(cocos2d::ValueMap &map);
};

#endif /* defined(__MasmorraDados__MonsterDiceFaceBuilder__) */
