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

class Character;

class Player : public GameObject {
  CC_SYNTHESIZE(Character*, _character, Character);
};

#endif /* defined(__MasmorraDados__Player__) */
