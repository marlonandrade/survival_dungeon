//
//  MonsterDiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__MonsterDiceFace__
#define __MasmorraDados__MonsterDiceFace__

#include "DiceFace.h"

class Monster;

class MonsterDiceFace : public DiceFace {
public:
  CREATE_FUNC(MonsterDiceFace);
  
  CC_SYNTHESIZE(Monster*, monster, Monster);
};

#endif /* defined(__MasmorraDados__MonsterDiceFace__) */
