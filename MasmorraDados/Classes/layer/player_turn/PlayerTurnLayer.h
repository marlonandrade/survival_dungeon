//
//  PlayerTurnLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#ifndef __MasmorraDados__PlayerTurnLayer__
#define __MasmorraDados__PlayerTurnLayer__

#include "cocos2d.h"

class DiceSelectLayer;
class GameplayLayer;

class PlayerTurnLayer : public cocos2d::Layer {
public:
  virtual bool init();
  CREATE_FUNC(PlayerTurnLayer);
  
  void playerTurnHasStarted();
  
  void showDiceSelectLayer();
  void showGameplayLayer();

private:
  DiceSelectLayer* _getDiceSelectLayer();
  GameplayLayer* _getGameplayLayer();
  
  void _setupChildren();
  void _setupEventHandlers();
};

#endif /* defined(__MasmorraDados__PlayerTurnLayer__) */
