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

#include "CharacterMoveDelegate.h"
#include "Game.h"
#include "MonsterRoomData.h"
#include "Turn.h"

class GameplayScene : public cocos2d::Scene, CharacterMoveDelegate {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _turnHasStartedListener,
                       TurnHasStartedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _turnHasEndedListener,
                       TurnHasEndedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _actionDicesRolledListener,
                       ActionDicesRolledListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _monsterDiceGeneratedListener,
                       MonsterDiceGeneratedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _lastTileHasBeenPlacedListener,
                       LastTileHasBeenPlacedListener);
  
  CC_SYNTHESIZE_RETAIN(Game*, _game, Game);
  CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Node*>, _interactableNodes, InteractableNodes);
  
protected:
  bool _userInteractionEnabled;
  cocos2d::Vector<MonsterRoomData*> _monsterRoomDatas;
  
public:
  virtual bool init();
  CREATE_FUNC(GameplayScene);
  
private:
  void _adjustInitialLayers();
  
  void _setupEventHandlers();
  
  cocos2d::Layer* _createObjectsLayer();
  cocos2d::Layer* _createControlsLayer();
  
  cocos2d::Node* _createCharacterDiceSprite();
  
  cocos2d::Layer* _getScrollableLayer();
  cocos2d::Layer* _getObjectsLayer();
  cocos2d::Layer* _getControlsLayer();
  
  void _roomsHasBeenPlaced(cocos2d::Vector<RoomPlacementData*> placements);
  
  cocos2d::Vec2 _positionInScene(cocos2d::Vec2 gameCoordinate);
  cocos2d::Vec2 _positionInGameCoordinate(cocos2d::Vec2 scenePosition);
  std::string _nameForGameCoordinate(cocos2d::Vec2 gameCoordinate);
  
  void _adjustCharacterDiceSpritePosition();
  
  void _addOverlayWithVisibleNodes(cocos2d::Vector<Node*> visibleNodes);
  void _removeOverlay();
  
  cocos2d::Vec2 _centerOfScene();
  
  cocos2d::Node* _getNodeForCharacterPosition();
  cocos2d::Node* _getNodeForPosition(cocos2d::Vec2 position);
  cocos2d::Vector<cocos2d::Node*> _getNodesForAdjacentCharacterPosition();
  
  bool _isInteractionEnabled();
  void _disableInteractions();
  void _enableInteractions();
  
  void _resetCharacterMoveState();
  
  void _showPlayerTurnInfo();
  void _showDungeonTurnInfo();
  void _showTurnInfo(cocos2d::Sprite* infoSprite);
  
#pragma mark - Events
  void _handleTurnHasStarted(cocos2d::EventCustom* event);
  void _handleTurnHasEnded(cocos2d::EventCustom* event);
  void _handleActionDicesRolled(cocos2d::EventCustom* event);
  void _handleMonsterDiceGenerated(cocos2d::EventCustom* event);
  void _handleLastTileHasBeenPlaced(cocos2d::EventCustom* event);
  
public:
#pragma mark - Character Move Delegate
  virtual bool canCharacterMove();
  virtual void characterWillMove(CharacterDiceSprite* sprite);
  virtual void characterIsMovingToLocation(cocos2d::Vec2 location);
  virtual bool canCharacterMoveToLocation(cocos2d::Vec2 location);
  virtual void characterMovedToLocation(CharacterDiceSprite* sprite, cocos2d::Vec2 location);
  virtual void characterDidNotMove(CharacterDiceSprite* sprite);
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
