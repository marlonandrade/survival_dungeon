//
//  DiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 23/02/2015.
//
//

#ifndef __MasmorraDados__DiceFace__
#define __MasmorraDados__DiceFace__

#include "GameObject.h"

class Dice;

class DiceFace : public GameObject {
  CC_SYNTHESIZE(Dice*, _dice, Dice);
};

#endif /* defined(__MasmorraDados__DiceFace__) */
