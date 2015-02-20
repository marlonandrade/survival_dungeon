//
//  ActionDiceRoller.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 20/02/2015.
//
//

#include "ActionDiceRoller.h"

#include "ActionDice.h"
#include "Definitions.h"
#include "Dice.h"

USING_NS_CC;

bool ActionDiceRoller::init()
{
    Vector<Dice *> actionDices;
    
    for (int i = 0; i < 6; i++)
    {
        actionDices.pushBack(ActionDice::create());
    }
    
    if (!DiceRoller::initWithDices(actionDices))
    {
        return false;
    }
    
    return true;
}

Vector<DiceFace*> ActionDiceRoller::reroll(cocos2d::Vector<DiceFace *> rolledFaces)
{
    if (this->getRerolls() < MAX_ACTION_REROLLS)
    {
        return DiceRoller::reroll(rolledFaces);
    }
    else
    {
        throw NO_REROLL_AVAILABLE;
    }
}