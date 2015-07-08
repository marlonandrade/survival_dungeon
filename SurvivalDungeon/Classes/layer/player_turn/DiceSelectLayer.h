//
//  DiceSelectLayer.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#ifndef __SurvivalDungeon__DiceSelectLayer__
#define __SurvivalDungeon__DiceSelectLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "ActionDice.h"

class DiceSelectLayer : public cocos2d::Layer {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _diceStateNewListener,
                       DiceStateNewListener);
  
  CC_SYNTHESIZE(cocos2d::Vector<ActionDice*>, _dices, Dices);
public:
  CREATE_FUNC(DiceSelectLayer);
  virtual bool init();
  
  void showDices();
  
  void resetRollCount();
  void resetActionDicesZIndex();
  
private:
  int _rollCount;
  
  void _setupChilds(cocos2d::Vector<ActionDice*> dices);
  cocos2d::Node* _createActionDices(cocos2d::Vector<ActionDice*> dices);
  cocos2d::Node* _createRerollButton();
  cocos2d::Node* _createOkButton();
  void _setupEventHandlers();
  
  void _setRerollButtonEnabled(bool enabled);
  void _adjustRerollButtonTextures();
  
  cocos2d::ui::Button* _getRerollButton();
  
#pragma mark - Events
  void _handleRerollTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void _handleOkTouched(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type);
  void _handleDiceStateNew(cocos2d::EventCustom* event);
};

#endif /* defined(__SurvivalDungeon__DiceSelectLayer__) */
