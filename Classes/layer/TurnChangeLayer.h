//
//  TurnChangeLayer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#ifndef __SurvivalDungeon__TurnChangeLayer__
#define __SurvivalDungeon__TurnChangeLayer__

#include "cocos2d.h"

class TurnChangeLayer : public cocos2d::Layer {
  CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _dungeonInfo, DungeonInfo);
  CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _playerInfo, PlayerInfo);
public:
  CREATE_FUNC(TurnChangeLayer);
  virtual bool init();
  
  void showPlayerTurnInfo();
  void showDungeonTurnInfo();
  
private:
  void _setupChildren();
  
  cocos2d::LayerColor* _getOverlayLayer();
  cocos2d::Node* _getInfo();
  
  void _showInfo(cocos2d::Sprite* infoSprite);
};

#endif /* defined(__SurvivalDungeon__TurnChangeLayer__) */
