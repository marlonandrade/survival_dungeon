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

class Credits : public InnerMenu
{
public:
    static cocos2d::Scene *createScene();
    virtual bool init();
    
    CREATE_FUNC(Credits);
};

#endif /* defined(__MasmorraDados__CreditsScene__) */
