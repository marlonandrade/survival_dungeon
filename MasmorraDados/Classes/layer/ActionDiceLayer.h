//
//  ActionDiceLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/19/15.
//
//

#ifndef __MasmorraDados__ActionDiceLayer__
#define __MasmorraDados__ActionDiceLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "ActionDice.h"

class ActionDiceLayer : public cocos2d::Layer {
  CC_SYNTHESIZE(cocos2d::Vector<ActionDice*>, _dices, Dices);
public:
  static ActionDiceLayer* createWithDices(cocos2d::Vector<ActionDice*> dices);
  virtual bool initWithDices(cocos2d::Vector<ActionDice*> dices);
  void resetRollCount();
  
#pragma mark - Events
  virtual void handleDiceStateNew(cocos2d::EventCustom* event);
private:
  int _rollCount;
  
  void _setupChilds(cocos2d::Vector<ActionDice*> dices);
  cocos2d::Node* _createActionDices(cocos2d::Vector<ActionDice*> dices);
  cocos2d::Node* _createRerollButton();
  cocos2d::Node* _createOkButton();
  
  void _setRerollButtonEnabled(bool enabled);
  void _adjustRerollButtonTextures();
  
  cocos2d::ui::Button* _getRerollButton();
};

#endif /* defined(__MasmorraDados__ActionDiceLayer__) */
