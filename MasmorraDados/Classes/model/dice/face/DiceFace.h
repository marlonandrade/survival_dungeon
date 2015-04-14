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
  CC_SYNTHESIZE(std::string, _imagePath, ImagePath);
public:
  static DiceFace* createWithImagePath(std::string imagePath);
  virtual bool initWithImagePath(std::string imagePath);
};

#endif /* defined(__MasmorraDados__DiceFace__) */
