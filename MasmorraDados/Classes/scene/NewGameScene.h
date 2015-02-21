//
//  NewGameScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__NewGameScene__
#define __MasmorraDados__NewGameScene__

#include "InnerMenuLayer.h"

class NewGameScene : public InnerMenu
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  CREATE_FUNC(NewGameScene);
};

#endif /* defined(__MasmorraDados__NewGameScene__) */
