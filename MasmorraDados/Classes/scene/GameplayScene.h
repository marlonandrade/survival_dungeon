//
//  GameplayScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__GameplayScene__
#define __MasmorraDados__GameplayScene__

#include "cocos2d.h"

class GameplayScene : public cocos2d::Layer {
public:
  static cocos2d::Scene *createScene();
  virtual bool init();
  
  CREATE_FUNC(GameplayScene);
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
