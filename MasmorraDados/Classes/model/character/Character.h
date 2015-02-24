//
//  Character.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Character__
#define __MasmorraDados__Character__

#include "GameObject.h"

class Character : public GameObject {
public:
  Character();
  
  virtual std::string getName() = 0;
  virtual std::string getImagePath() = 0;
};

#endif /* defined(__MasmorraDados__Character__) */
