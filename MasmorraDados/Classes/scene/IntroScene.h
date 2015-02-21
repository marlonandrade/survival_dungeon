//
//  IntroScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#ifndef __MasmorraDados__IntroScene__
#define __MasmorraDados__IntroScene__

#include "cocos2d.h"

class IntroScene : public cocos2d::Layer {
public:
  static cocos2d::Scene* createScene();
  virtual bool init();
  
  CREATE_FUNC(IntroScene);
private:
  void loadResources(float deltaTime);
};

#endif /* defined(__MasmorraDados__IntroScene__) */
