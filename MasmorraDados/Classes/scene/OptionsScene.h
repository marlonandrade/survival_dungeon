//
//  OptionsScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__OptionsScene__
#define __MasmorraDados__OptionsScene__

#include "cocos2d.h"
#include "InnerMenuLayer.h"

class OptionsScene : public InnerMenuLayer {
public:
  static cocos2d::Scene *createScene();
  virtual bool init();
  
  CREATE_FUNC(OptionsScene);
};

#endif /* defined(__MasmorraDados__OptionsScene__) */
