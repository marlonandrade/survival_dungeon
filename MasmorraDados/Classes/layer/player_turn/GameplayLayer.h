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
#include "ui/CocosGUI.h"

class Dice;

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
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _freeBootSpentListener,
                       FreeBootSpentListener);
public:
  CREATE_FUNC(GameplayLayer);
  virtual bool init();
  
  void migrateDicesAndShow();
  
  void resetFreeBootUsed();
  void resetDockableNodes();
  
  cocos2d::Vector<Node*> getDockableNodes();
private:
  void _setupFreeBootSymbol();
  void _setupDockableDice();
  void _setupFinalizarButton();
  void _setupEventHandlers();
  
  cocos2d::Node* _getDockContainer();
  
  void _triggerMagicDiceOnTargetDice(Dice* targetDice);
  
  void _addOverlay(cocos2d::Vector<Node*> targetNodes);
  void _removeOverlay();
#pragma mark - UI Events
  void _handleEndTurnTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  
#pragma mark - Event Handlers
  void _handleActionDiceDragStarted(cocos2d::EventCustom* event);
  void _handleActionDiceDragMoved(cocos2d::EventCustom* event);
  void _handleActionDiceDragEnded(cocos2d::EventCustom* event);
  void _handleActionFreeBootSpent(cocos2d::EventCustom* event);
};

#endif /* defined(__MasmorraDados__GameplayLayer__) */
