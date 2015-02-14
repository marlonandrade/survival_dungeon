//
//  MainMenuScene.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#ifndef __MasmorraDados__MainMenuScene__
#define __MasmorraDados__MainMenuScene__

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(MainMenu);
private:
    virtual cocos2d::Menu* createMenu();
};

#endif /* defined(__MasmorraDados__MainMenuScene__) */
