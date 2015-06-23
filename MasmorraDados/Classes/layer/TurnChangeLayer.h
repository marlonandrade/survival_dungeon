//
//  TurnChangeLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#ifndef __MasmorraDados__TurnChangeLayer__
#define __MasmorraDados__TurnChangeLayer__

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

#endif /* defined(__MasmorraDados__TurnChangeLayer__) */
