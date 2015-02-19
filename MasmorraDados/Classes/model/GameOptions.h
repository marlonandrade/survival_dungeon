//
//  GameOptions.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 15/02/2015.
//
//

#ifndef __MasmorraDados__GameOptions__
#define __MasmorraDados__GameOptions__

#include "GameObject.h"

class GameOptions : public GameObject
{
public:
    virtual bool init();
    CREATE_FUNC(GameOptions);
    
    CC_SYNTHESIZE(int, requireXpToWin, RequiredXpToWin);
};

#endif /* defined(__MasmorraDados__GameOptions__) */
