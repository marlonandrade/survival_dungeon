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

#include "Game.h"

class GameplayScene : public cocos2d::Scene {
  CC_SYNTHESIZE_RETAIN(Game*, _game, Game);
  
public:
  virtual bool init();
  CREATE_FUNC(GameplayScene);
  
private:
  cocos2d::Layer* getDungeonLayer();
  void adjustInitialLayers();
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
