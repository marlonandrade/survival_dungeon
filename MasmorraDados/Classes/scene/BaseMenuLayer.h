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

class BaseMenu : public cocos2d::Layer
{
public:
    virtual bool init(std::string title);
};

#endif /* defined(__MasmorraDados__BaseMenuLayer__) */
