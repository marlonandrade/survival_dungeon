//
//  SoloGame.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 22/02/2015.
//
//

#ifndef __MasmorraDados__SoloGame__
#define __MasmorraDados__SoloGame__

#include "Game.h"

class SoloGame : public Game {
public:
  virtual bool init();
  CREATE_FUNC(SoloGame);
};

#endif /* defined(__MasmorraDados__SoloGame__) */
