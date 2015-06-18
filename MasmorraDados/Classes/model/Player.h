//
//  Player.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__Player__
#define __MasmorraDados__Player__

#include "GameObject.h"

#include "Character.h"

class Player : public GameObject {
  CC_SYNTHESIZE_RETAIN(Character*, _character, Character);
  CREATE_FUNC(Player);
  virtual bool init();
};

#endif /* defined(__MasmorraDados__Player__) */
