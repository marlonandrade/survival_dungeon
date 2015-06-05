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

#include "ActionDice.h"

class MagicDiceEffectLayer : public cocos2d::Layer {
  CC_SYNTHESIZE_RETAIN(ActionDice*, _magicDice, MagicDice);
  CC_SYNTHESIZE_RETAIN(ActionDice*, _targetDice, TargetDice);
public:
  CREATE_FUNC(MagicDiceEffectLayer);
  virtual bool init();
  
  void triggerEffect(ActionDice* magicDice, ActionDice* targetDice, cocos2d::Layer* layer);
  
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__MagicDiceEffectLayer__) */
