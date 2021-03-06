//
//  CharacterDiceSprite.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __SurvivalDungeon__CharacterDiceSprite__
#define __SurvivalDungeon__CharacterDiceSprite__

#include "cocos2d.h"

#include "CharacterMoveDelegate.h"

class CharacterDiceSprite : public cocos2d::Sprite {
  CC_SYNTHESIZE(CharacterMoveDelegate*, _delegate, Delegate);
  CC_PROPERTY(int, _damageTaken, DamageTaken);
  
public:
  CREATE_FUNC(CharacterDiceSprite);
  bool init();
  
  void setHitPoints(int hitPoints);
  void resetDamageTaken();
  void takeDamage(int damage);
  
private:
  void _setupTouchListener();
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__SurvivalDungeon__CharacterDiceSprite__) */
