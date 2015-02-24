//
//  CharacterSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 24/02/2015.
//
//

#ifndef __MasmorraDados__CharacterSprite__
#define __MasmorraDados__CharacterSprite__

#include "cocos2d.h"

class CharacterSprite : public cocos2d::Sprite {
public:
  virtual bool init();
  CREATE_FUNC(CharacterSprite);
  
  void setHitpoints(int hitpoints);
  
private:
  std::string getFileNameForHitpoints(int hitpoints);
};

#endif /* defined(__MasmorraDados__CharacterSprite__) */
