//
//  Monster.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Monster__
#define __MasmorraDados__Monster__

#include "GameObject.h"

class Monster : public GameObject
{
public:
    CREATE_FUNC(Monster);
    
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(std::string, _kind, Kind);
    CC_SYNTHESIZE(int, _attack, Attack);
    CC_SYNTHESIZE(int, _defense, Defense);
    CC_SYNTHESIZE(int, _xp, Xp);
    CC_SYNTHESIZE(cocos2d::ValueVector, _specials, Specials);
};

#endif /* defined(__MasmorraDados__Monster__) */
