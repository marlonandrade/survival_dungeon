//
//  GameplayLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/27/15.
//
//

#ifndef __MasmorraDados__GameplayLayer__
#define __MasmorraDados__GameplayLayer__

#include "cocos2d.h"

class DockableContainer;
class FreeBootSprite;

class GameplayLayer : public cocos2d::Layer {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _diceDragStartedListener,
                       DiceDragStartedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _diceDragMovedListener,
                       DiceDragMovedListener);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _diceDragEndedListener,
                       DiceDragEndedListener);
  
public:
  CREATE_FUNC(GameplayLayer);
  virtual bool init();
  
  void migrateDicesAndShow();
  
  void resetFreeBootUsed();
  void resetDockableNodes();
  
private:
  void _setupChildren();
  void _setupEventHandlers();
  
  cocos2d::Sprite* _createFreeBootSprite();
  DockableContainer* _createDockableContainer();
  cocos2d::Node* _createFinalizarButton();
  
  FreeBootSprite* _getFreeBootSprite();
  DockableContainer* _getDockableContainer();
  
#pragma mark - Event Handlers
  void _handleActionDiceDragStarted(cocos2d::EventCustom* event);
  void _handleActionDiceDragMoved(cocos2d::EventCustom* event);
  void _handleActionDiceDragEnded(cocos2d::EventCustom* event);
};

#endif /* defined(__MasmorraDados__GameplayLayer__) */
