//
//  DiceSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __MasmorraDados__DiceSprite__
#define __MasmorraDados__DiceSprite__

#include "cocos2d.h"

#include "Dice.h"

class DiceSprite : public cocos2d::Sprite {
  CC_SYNTHESIZE(Dice*, _dice, Dice);
  
public:
  static DiceSprite* createWithDice(Dice* dice);
  virtual bool initWithDice(Dice* dice);
};

#endif /* defined(__MasmorraDados__DiceSprite__) */
