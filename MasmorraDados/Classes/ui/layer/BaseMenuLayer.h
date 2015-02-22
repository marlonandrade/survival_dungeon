//
//  BaseMenuLayer.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__BaseMenuLayer__
#define __MasmorraDados__BaseMenuLayer__

#include "cocos2d.h"
#include "ExitLayer.h"

class BaseMenuLayer : public ExitLayer {
public:
  virtual bool init(std::string title);
  virtual void leave();
};

#endif /* defined(__MasmorraDados__BaseMenuLayer__) */
