//
//  GameOptions.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__GameOptions__
#define __MasmorraDados__GameOptions__

#include "GameObject.h"

class GameOptions : public GameObject {
  CC_SYNTHESIZE(int, _requireXpToWin, RequiredXpToWin);
  
public:
  virtual bool init();
  CREATE_FUNC(GameOptions);
};

#endif /* defined(__MasmorraDados__GameOptions__) */
