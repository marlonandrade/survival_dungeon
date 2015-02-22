//
//  ExitLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__ExitLayer__
#define __MasmorraDados__ExitLayer__

#include "cocos2d.h"

class ExitLayer : public cocos2d::Layer {
public:
  virtual bool init();
  virtual void leave();
  
  virtual void onEnter();
  virtual void onExit();
  virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode,
                             cocos2d::Event *event);
};

#endif /* defined(__MasmorraDados__ExitLayer__) */
