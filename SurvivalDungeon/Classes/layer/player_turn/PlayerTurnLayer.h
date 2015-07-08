//
//  PlayerTurnLayer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#ifndef __SurvivalDungeon__PlayerTurnLayer__
#define __SurvivalDungeon__PlayerTurnLayer__

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
};

#endif /* defined(__SurvivalDungeon__PlayerTurnLayer__) */
