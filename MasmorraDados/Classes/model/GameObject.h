//
//  GameObject.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__GameObject__
#define __MasmorraDados__GameObject__

#include "cocos2d.h"

class GameObject : public cocos2d::Ref {
public:
  virtual bool init();
  CREATE_FUNC(GameObject);
};

#endif /* defined(__MasmorraDados__GameObject__) */
