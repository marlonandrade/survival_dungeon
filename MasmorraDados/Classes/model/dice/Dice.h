//
//  Dice.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Dice__
#define __MasmorraDados__Dice__

#include "GameObject.h"

class DiceFace;

class Dice : public GameObject
{
public:
    static Dice* createWithPlist(const char* fileName);
    bool initWithPlist(const char* fileName);
    
    virtual DiceFace* roll();
protected:
    std::vector<DiceFace*> _faces;
};

#endif /* defined(__MasmorraDados__Dice__) */
