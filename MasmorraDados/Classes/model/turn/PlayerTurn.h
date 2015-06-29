//
//  PlayerTurn.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/7/15.
//
//

#ifndef __MasmorraDados__PlayerTurn__
#define __MasmorraDados__PlayerTurn__

#include "cocos2d.h"
#include "Turn.h"

class PlayerTurn : public Turn {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _actionDicesRolledListener,
                       ActionDicesRolledListener);
  CC_PROPERTY(int, _damageProtected, DamageProtected);
protected:
  bool _actionDicesRolled;
public:
  CREATE_FUNC(PlayerTurn);
  virtual bool init();
  
  void protectDamage(int damage);
  bool isActionDicesRolled();
  
  virtual void finish(Game* game);
  
private:
  void _setupEventHandlers();
  
#pragma mark - Events
  void _handleActionDicesRolled(cocos2d::EventCustom* event);
};


#endif /* defined(__MasmorraDados__PlayerTurn__) */
