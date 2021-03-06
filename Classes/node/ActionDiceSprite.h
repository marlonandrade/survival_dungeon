//
//  ActionDiceSprite.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#ifndef __SurvivalDungeon__ActionDiceSprite__
#define __SurvivalDungeon__ActionDiceSprite__

#include "DiceSprite.h"

class ActionDice;

class ActionDiceSprite : public DiceSprite {
  CC_SYNTHESIZE(cocos2d::Vec2, _originalPosition, OriginalPosition);
public:
  static ActionDiceSprite* createWithDice(Dice* dice);
  virtual bool initWithDice(Dice* dice);
  
  void dockOnNode(cocos2d::Node* node);
  void undock(cocos2d::Layer* layer);
  
  void startDragging();
  
  void restoreOriginalPosition();
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__SurvivalDungeon__ActionDiceSprite__) */
