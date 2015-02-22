//
//  CreditsScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__CreditsScene__
#define __MasmorraDados__CreditsScene__

#include "cocos2d.h"
#include "InnerMenuLayer.h"

class CreditsScene : public InnerMenuLayer {
public:
  static cocos2d::Scene *createScene();
  virtual bool init();
  
  CREATE_FUNC(CreditsScene);
};

#endif /* defined(__MasmorraDados__CreditsScene__) */
