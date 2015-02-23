//
//  DiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__DiceFace__
#define __MasmorraDados__DiceFace__

#include "GameObject.h"

class Dice;

class DiceFace : public GameObject {
  CC_SYNTHESIZE(Dice*, _dice, Dice);
  CC_SYNTHESIZE(std::string, _imageName, ImageName);
  
public:
  CREATE_FUNC(DiceFace);
};

#endif /* defined(__MasmorraDados__DiceFace__) */
