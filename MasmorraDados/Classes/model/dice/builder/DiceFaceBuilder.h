//
//  DiceFaceBuilder.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__DiceFaceBuilder__
#define __MasmorraDados__DiceFaceBuilder__

#include "GameObject.h"

class DiceFace;

class DiceFaceBuilder : public GameObject {
public:
  CREATE_FUNC(DiceFaceBuilder);
  virtual DiceFace* diceFace(cocos2d::ValueMap &map);
};

#endif /* defined(__MasmorraDados__DiceFaceBuilder__) */
