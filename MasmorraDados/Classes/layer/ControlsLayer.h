//
//  ControlsLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/2/15.
//
//

#ifndef __MasmorraDados__ControlsLayer__
#define __MasmorraDados__ControlsLayer__

#include "cocos2d.h"

class ActionDiceLayer;
class PlayerSkillsLayer;

class ControlsLayer : public cocos2d::Layer {
public:
  virtual bool init();
  CREATE_FUNC(ControlsLayer);
  
  void playerTurnHasStarted();
  
  void showActionDices();
  void showPlayerSkillsLayer();

private:
  ActionDiceLayer* _getActionDiceLayer();
  PlayerSkillsLayer* _getPlayerSkillsLayer();
  
  void _setupChildren();
  void _setupEventHandlers();
};

#endif /* defined(__MasmorraDados__ControlsLayer__) */
