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

#include "ActionDice.h"

class ActionDiceLayer : public cocos2d::Layer {
public:
  static ActionDiceLayer* createWithDices(cocos2d::Vector<ActionDice*> dices);
  virtual bool initWithDices(cocos2d::Vector<ActionDice*> dices);
  
private:
  void _setupActionDices(cocos2d::Vector<ActionDice*> dices);
};

#endif /* defined(__MasmorraDados__ActionDiceLayer__) */
