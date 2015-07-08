//
//  Character.h
//  SurvivalDungeon
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __SurvivalDungeon__Character__
#define __SurvivalDungeon__Character__

#include "GameObject.h"

#include "CharacterDiceSprite.h"

class Character : public GameObject {
  CC_SYNTHESIZE_RETAIN(CharacterDiceSprite*, _sprite, Sprite);
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _damageTakenListener,
                       DamageTakenListener);
  
  CC_PROPERTY(int, _hitPoints, HitPoints);
  
  CREATE_FUNC(Character);
  bool init();
  
  void takeDamage(int damage);
  void heal(int amount);
  
  void resetLife();
  bool isLifeFull();
  
private:
  void _setupEventHandlers();
  
  void _handleDamageTaken(cocos2d::EventCustom* event);
};

#endif /* defined(__SurvivalDungeon__Character__) */
