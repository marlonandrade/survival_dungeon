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
#include "Turn.h"

class BackgroundLayer;
class ControlsLayer;

class GameplayScene : public cocos2d::Scene {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _actionDicesRolledListener,
                       ActionDicesRolledListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _turnHasStartedListener,
                       TurnHasStartedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _turnHasEndedListener,
                       TurnHasEndedListener);
  
public:
  virtual bool init();
  CREATE_FUNC(GameplayScene);
  
private:
  void _adjustInitialLayers();
  
  void _setupEventHandlers();
  
  BackgroundLayer* _getScrollableLayer();
  ControlsLayer* _getControlsLayer();
  
  void _roomsHasBeenPlaced(cocos2d::Vector<RoomPlacementData*> placements);
  
  void _showPlayerTurnInfo();
  void _showDungeonTurnInfo();
  void _showTurnInfo(cocos2d::Sprite* infoSprite);
  
  void _showActionDicesLayer();
  void _showPlayerSkillsLayer();
  
#pragma mark - Events
  void _handleActionDicesRolled(cocos2d::EventCustom* event);
  void _handleTurnHasStarted(cocos2d::EventCustom* event);
  void _handleTurnHasEnded(cocos2d::EventCustom* event);
  
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
