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
  void adjustInitialLayers();
  
  cocos2d::Layer* _createDungeonLayer();
  cocos2d::Layer* _createGameObjectsLayer();
  cocos2d::Layer* _createControlsLayer();
  
  cocos2d::Layer* getDungeonLayer();
  cocos2d::Layer* getGameObjectsLayer();
  cocos2d::Layer* getControlsLayer();
  
  void _adjustCharacterSpritePosition();
  
  cocos2d::Vec2 _centerOfScene();
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
