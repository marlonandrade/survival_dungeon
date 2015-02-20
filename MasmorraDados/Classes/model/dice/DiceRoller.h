//
//  DiceRoller.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 20/02/2015.
//
//

#ifndef __MasmorraDados__DiceRoller__
#define __MasmorraDados__DiceRoller__

#include "GameObject.h"

class Dice;
class DiceFace;

class DiceRoller : public GameObject
{
public:
    static DiceRoller* createWithDices(const cocos2d::Vector<Dice*> dices);
    virtual bool initWithDices(const cocos2d::Vector<Dice*> dices);
    
    virtual cocos2d::Vector<DiceFace*> roll();
    virtual cocos2d::Vector<DiceFace*> reroll(cocos2d::Vector<DiceFace*> dices);
    
    CC_SYNTHESIZE(cocos2d::Vector<Dice*>, dices, Dices);
    CC_SYNTHESIZE(int, rerolls, Rerolls);
};


#endif /* defined(__MasmorraDados__DiceRoller__) */
