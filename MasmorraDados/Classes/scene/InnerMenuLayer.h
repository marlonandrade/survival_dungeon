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

class InnerMenu : public BaseMenu
{
public:
    virtual bool init(std::string title);
    
    virtual void onEnter();
    virtual void onExit();
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
};


#endif /* defined(__MasmorraDados__InnerMenuLayer__) */
