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
#include "DiceFace.h"

class DiceFaceBuilder;

class Dice : public GameObject {
  CC_SYNTHESIZE(cocos2d::Vector<DiceFace*>, _faces, Faces);
  
public:
  static Dice* createWithPlist(const char* fileName, DiceFaceBuilder* builder);
  virtual bool initWithPlist(const char* fileName, DiceFaceBuilder* builder);
  
  virtual DiceFace* roll();
};

#endif /* defined(__MasmorraDados__Dice__) */
