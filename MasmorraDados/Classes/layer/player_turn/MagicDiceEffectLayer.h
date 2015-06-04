//
//  MagicDiceEffectLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__MagicDiceEffectLayer__
#define __MasmorraDados__MagicDiceEffectLayer__

#include "cocos2d.h"

class Dice;

class MagicDiceEffectLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(MagicDiceEffectLayer);
  virtual bool init();
  
  void triggerEffectOnTarget(Dice* targetDice, cocos2d::Layer* layer);
  
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__MagicDiceEffectLayer__) */
