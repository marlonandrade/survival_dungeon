//
//  ActionDiceSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#ifndef __MasmorraDados__ActionDiceSprite__
#define __MasmorraDados__ActionDiceSprite__

#include "cocos2d.h"
#include "ActionDiceState.h"

class ActionDice;
class ActionDiceState;

class ActionDiceSprite : public cocos2d::Sprite {
public:
  CREATE_FUNC(ActionDiceSprite);
  CC_SYNTHESIZE_RETAIN(ActionDiceState*, _diceState, DiceState);
  
  virtual bool init();
private:
  void _setupTouchListener();
  std::string _getFileNameForDice(ActionDice* dice);
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__ActionDiceSprite__) */
