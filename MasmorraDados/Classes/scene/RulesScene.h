//
//  RulesScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#ifndef __MasmorraDados__RulesScene__
#define __MasmorraDados__RulesScene__

#include "cocos2d.h"
#include "InnerMenuLayer.h"

class Rules : public InnerMenu
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    
    CREATE_FUNC(Rules);
};

#endif /* defined(__MasmorraDados__RulesScene__) */
