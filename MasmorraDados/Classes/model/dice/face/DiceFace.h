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
public:
  CREATE_FUNC(DiceFace);
  
  CC_SYNTHESIZE(Dice*, dice, Dice);
  CC_SYNTHESIZE(std::string, imageName, ImageName);
};

#endif /* defined(__MasmorraDados__DiceFace__) */
