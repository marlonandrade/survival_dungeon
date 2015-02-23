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

class Game;

class NewGameScene : public InnerMenuLayer {
  CC_SYNTHESIZE(Game*, _game, Game);
  CC_SYNTHESIZE_RETAIN(cocos2d::MenuItem*, _jogarMenuItem, JogarMenuItem);
  
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  CREATE_FUNC(NewGameScene);
private:
  cocos2d::Layer* characterSelectLayer();
  cocos2d::Menu *iniciarMenu();
};

#endif /* defined(__MasmorraDados__NewGameScene__) */
