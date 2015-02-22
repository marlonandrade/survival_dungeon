//
//  InnerMenuLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__InnerMenuLayer__
#define __MasmorraDados__InnerMenuLayer__

#include "cocos2d.h"
#include "BaseMenuLayer.h"

class InnerMenuLayer : public BaseMenuLayer {
public:
  virtual bool init(std::string title);
  virtual void leave();
};

#endif /* defined(__MasmorraDados__InnerMenuLayer__) */
