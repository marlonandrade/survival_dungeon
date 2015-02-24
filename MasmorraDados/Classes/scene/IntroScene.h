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

class IntroScene : public cocos2d::Scene {
public:
  virtual bool init();
  CREATE_FUNC(IntroScene);
private:
  void loadResources(float deltaTime);
};

#endif /* defined(__MasmorraDados__IntroScene__) */
