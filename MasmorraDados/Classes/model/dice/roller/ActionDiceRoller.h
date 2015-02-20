//
//  ActionDiceRoller.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 20/02/2015.
//
//

#ifndef __MasmorraDados__ActionDiceRoller__
#define __MasmorraDados__ActionDiceRoller__

#include "DiceRoller.h"

class ActionDiceRoller : public DiceRoller
{
public:
    CREATE_FUNC(ActionDiceRoller);
    virtual bool init();
    
    virtual cocos2d::Vector<DiceFace *> reroll(cocos2d::Vector<DiceFace *> rolledFaces);
};

#endif /* defined(__MasmorraDados__ActionDiceRoller__) */
