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
public:
  CREATE_FUNC(TurnChangeLayer);
  virtual bool init();
  
  void showPlayerTurnInfo();
  void showDungeonTurnInfo();
  
private:
  void _setupChildren();
  
  cocos2d::LayerColor* _getOverlayLayer();
  cocos2d::Sprite* _getSprite();
  
  void _showInfo(const std::string &filename);
};

#endif /* defined(__MasmorraDados__TurnChangeLayer__) */
