//
//  CharacterMoveDelegate.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/6/15.
//
//

#ifndef __MasmorraDados__CharacterMoveDelegate__
#define __MasmorraDados__CharacterMoveDelegate__

#include "cocos2d.h"

class CharacterDiceSprite;

class CharacterMoveDelegate {
public:
  virtual bool canCharacterMove() = 0;
  virtual void characterWillMove(CharacterDiceSprite* sprite) = 0;
  virtual void characterIsMovingToLocation(cocos2d::Vec2 location) = 0;
  virtual bool canCharacterMoveToLocation(cocos2d::Vec2 location) = 0;
  virtual void characterMovedToLocation(CharacterDiceSprite* sprite, cocos2d::Vec2 location) = 0;
  virtual void characterDidNotMove(CharacterDiceSprite* sprite) = 0;
};

#endif /* defined(__MasmorraDados__CharacterMoveDelegate__) */
