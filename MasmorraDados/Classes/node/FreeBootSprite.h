//
//  FreeBootSprite.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/4/15.
//
//

#ifndef __MasmorraDados__FreeBootSprite__
#define __MasmorraDados__FreeBootSprite__

#include "cocos2d.h"

class FreeBootSprite : public cocos2d::Sprite {
  CC_SYNTHESIZE_RETAIN(cocos2d::EventListenerCustom*,
                       _freeBootSpentListener,
                       FreeBootSpentListener);
  
public:
  CREATE_FUNC(FreeBootSprite);
  virtual bool init();
  
  void resetFreeBootUsed();
private:
  void _setupEventHandlers();
  
  void _handleActionFreeBootSpent(cocos2d::EventCustom* event);
};

#endif /* defined(__MasmorraDados__FreeBootSprite__) */
