//
//  GameOverScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 7/2/15.
//
//

#ifndef __MasmorraDados__GameOverScene__
#define __MasmorraDados__GameOverScene__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene {
public:
  CREATE_FUNC(GameOverScene);
  bool init();
  
private:
  void _setupChildren();
};

#endif /* defined(__MasmorraDados__GameOverScene__) */
