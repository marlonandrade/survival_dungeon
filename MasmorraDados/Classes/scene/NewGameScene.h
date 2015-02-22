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

class NewGameScene : public InnerMenuLayer
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  CREATE_FUNC(NewGameScene);
private:
  cocos2d::Layer* characterSelectLayer();
  cocos2d::Menu *iniciarMenu();
};

#endif /* defined(__MasmorraDados__NewGameScene__) */
