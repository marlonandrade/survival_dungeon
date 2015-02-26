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
  
  cocos2d::Layer* _getObjectsLayer();
  cocos2d::Layer* _getControlsLayer();
  
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
};

#endif /* defined(__MasmorraDados__GameplayScene__) */
