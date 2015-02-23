//
//  Game.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__Game__
#define __MasmorraDados__Game__

#include "cocos2d.h"

#include "Dungeon.h"
#include "GameObject.h"
#include "GameOptions.h"

class Game : public GameObject {
  CC_SYNTHESIZE_RETAIN(GameOptions*, _options, Options);
  CC_SYNTHESIZE_RETAIN(Dungeon*, _dungeon, Dungeon);
  
public:
  virtual bool init();
  CREATE_FUNC(Game);
};

#endif /* defined(__MasmorraDados__Game__) */
