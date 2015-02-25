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

class CharacterDiceSprite : public cocos2d::Sprite {
public:
  virtual bool init();
  CREATE_FUNC(CharacterDiceSprite);
  
  void setHitpoints(int hitpoints);
private:
  void _initializeEventListeners();
  std::string getFileNameForHitpoints(int hitpoints);
};

#endif /* defined(__MasmorraDados__CharacterDiceSprite__) */
