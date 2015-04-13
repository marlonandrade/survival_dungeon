//
//  ActionDiceStateSelected.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 4/13/15.
//
//

#ifndef __MasmorraDados__ActionDiceStateSelected__
#define __MasmorraDados__ActionDiceStateSelected__

#include "ActionDiceState.h"
#include "cocos2d.h"

class ActionDiceStateSelected : public ActionDiceState {
public:
  CREATE_FUNC(ActionDiceStateSelected);
  virtual bool init();
  
  virtual bool canChangeState();
  virtual void changeState(ActionDiceSprite *sprite);
};

#endif /* defined(__MasmorraDados__ActionDiceStateSelected__) */
