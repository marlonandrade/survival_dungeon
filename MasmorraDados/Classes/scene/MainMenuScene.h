//
//  MainMenuScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#ifndef __MasmorraDados__MainMenuScene__
#define __MasmorraDados__MainMenuScene__

#include "cocos2d.h"
#include "BaseMenuLayer.h"

class MainMenuScene : public BaseMenu {
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  virtual void leave();
  CREATE_FUNC(MainMenuScene);
private:
  virtual cocos2d::Menu* createMenu();
  cocos2d::LayerColor* getConfirmQuitLayer();
  cocos2d::LayerColor* _confirmQuitLayer;
};

#endif /* defined(__MasmorraDados__MainMenuScene__) */
