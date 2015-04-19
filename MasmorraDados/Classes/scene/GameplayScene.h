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

class GameplayScene : public cocos2d::Scene, CharacterMoveDelegate {
  CC_SYNTHESIZE_RETAIN(Game*, _game, Game);
  CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Node*>, _interactableNodes, InteractableNodes);
protected:
  bool _userInteractionEnabled;
  
public:
  virtual bool init();
  CREATE_FUNC(GameplayScene);
  
private:
  void adjustInitialLayers();
  
  cocos2d::Layer* _createObjectsLayer();
  cocos2d::Layer* _createControlsLayer();
  
  cocos2d::Node* _createCharacterDiceSprite();
  
  cocos2d::Layer* _getScrollableLayer();
  cocos2d::Layer* _getObjectsLayer();
  cocos2d::Layer* _getControlsLayer();
  
  void _roomsHasBeenPlaced(cocos2d::Vector<RoomPlacement*> placements);
  
  cocos2d::Vec2 _positionInScene(cocos2d::Vec2 gameCoordinate);
  cocos2d::Vec2 _positionInGameCoordinate(cocos2d::Vec2 scenePosition);
  std::string _nameForGameCoordinate(cocos2d::Vec2 gameCoordinate);
  
  void _adjustCharacterDiceSpritePosition();
  
  void _addOverlayWithVisibleNodes(cocos2d::Vector<Node*> visibleNodes);
  void _removeOverlay();
  
  cocos2d::Vec2 _centerOfScene();
  
  cocos2d::Node* _getNodeForCharacterPosition();
  cocos2d::Vector<cocos2d::Node*> _getNodesForAdjacentCharacterPosition();
  
  bool _isInteractionEnabled();
  void _disableInteractions();
  void _enableInteractions();
  
  void _resetCharacterMoveState();
public:
  virtual bool canCharacterMove();
  virtual void characterWillMove(CharacterDiceSprite* sprite);
  virtual void characterIsMovingToLocation(cocos2d::Vec2 location);
  virtual bool canCharacterMoveToLocation(cocos2d::Vec2 location);
  virtual void characterMovedToLocation(CharacterDiceSprite* sprite, cocos2d::Vec2 location);
  virtual void characterDidNotMove(CharacterDiceSprite* sprite);
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
