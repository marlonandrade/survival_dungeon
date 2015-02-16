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
#include "BaseMenuLayer.h"

class Options : public BaseMenu
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    
    CREATE_FUNC(Options);
};

#endif /* defined(__MasmorraDados__OptionsScene__) */
