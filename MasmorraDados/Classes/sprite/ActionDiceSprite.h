//
//  ActionDiceSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#ifndef __MasmorraDados__ActionDiceSprite__
#define __MasmorraDados__ActionDiceSprite__

#include "DiceSprite.h"

class ActionDice;

class ActionDiceSprite : public DiceSprite {
public:
  static ActionDiceSprite* createWithDice(Dice* dice);
  virtual bool initWithDice(Dice* dice);
  
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__ActionDiceSprite__) */
