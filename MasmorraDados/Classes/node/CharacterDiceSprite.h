//
//  CharacterDiceSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __MasmorraDados__CharacterDiceSprite__
#define __MasmorraDados__CharacterDiceSprite__

#include "cocos2d.h"

#include "CharacterMoveDelegate.h"

class CharacterDiceSprite : public cocos2d::Sprite {
  CC_SYNTHESIZE(CharacterMoveDelegate*, _delegate, Delegate);
  
public:
  static CharacterDiceSprite* createWithDelegate(CharacterMoveDelegate* delegate);
  virtual bool initWithDelegate(CharacterMoveDelegate* delegate);
  
  void setHitpoints(int hitpoints);
private:
  void _setupTouchListener();
  std::string _getFileNameForHitpoints(int hitpoints);
  
  bool _onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
  void _onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif /* defined(__MasmorraDados__CharacterDiceSprite__) */
