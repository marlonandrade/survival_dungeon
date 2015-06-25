//
//  HudLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 6/24/15.
//
//

#ifndef __MasmorraDados__HudLayer__
#define __MasmorraDados__HudLayer__

#include "cocos2d.h"

class HudLayer : public cocos2d::Layer {
public:
  CREATE_FUNC(HudLayer);
  bool init();
  
  void adjustLevel(int level);
private:
  void _setupChildren();
  
  cocos2d::Label* _getLevelLabel();
};

#endif /* defined(__MasmorraDados__HudLayer__) */
