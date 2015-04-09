//
//  ActionDiceSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/9/15.
//
//

#ifndef __MasmorraDados__ActionDiceSprite__
#define __MasmorraDados__ActionDiceSprite__

#include "cocos2d.h"

class ActionDice;

class ActionDiceSprite : public cocos2d::Sprite {
public:
  CREATE_FUNC(ActionDiceSprite);
  virtual bool init();
private:
  std::string _getFileNameForDice(ActionDice* dice);
};

#endif /* defined(__MasmorraDados__ActionDiceSprite__) */
