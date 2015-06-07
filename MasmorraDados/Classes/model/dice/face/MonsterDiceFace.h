//
//  MonsterDiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/7/15.
//
//

#ifndef __MasmorraDados__MonsterDiceFace__
#define __MasmorraDados__MonsterDiceFace__

#include "DiceFace.h"

class MonsterDiceFace : public DiceFace {
  CC_SYNTHESIZE(int, _attack, Attack);
  CC_SYNTHESIZE(int, _defense, Defense);
public:
  static MonsterDiceFace* create(std::string imagePath, int attack, int defense);
  virtual bool init(std::string imagePath, int attack, int defense);
};

#endif /* defined(__MasmorraDados__MonsterDiceFace__) */
