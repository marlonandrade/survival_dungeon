//
//  MajorMonsterDice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__MajorMonsterDice__
#define __MasmorraDados__MajorMonsterDice__

#include "Dice.h"

class MajorMonsterDice : public Dice
{
public:
    virtual bool init();
    CREATE_FUNC(MajorMonsterDice);
};

#endif /* defined(__MasmorraDados__MajorMonsterDice__) */
