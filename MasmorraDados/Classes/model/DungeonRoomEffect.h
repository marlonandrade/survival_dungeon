//
//  DungeonRoomEffect.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 22/02/2015.
//
//

#ifndef __MasmorraDados__DungeonRoomEffect__
#define __MasmorraDados__DungeonRoomEffect__

#include "GameObject.h"
#include "EffectType.h"
#include "EffectKind.h"

class DungeonRoomEffect : public GameObject {
  CC_SYNTHESIZE(EffectType, _type, Type);
  CC_SYNTHESIZE(EffectKind, _kind, Kind);
  CC_SYNTHESIZE(std::string, _description, Description);
  
public:
  CREATE_FUNC(DungeonRoomEffect);
};

#endif /* defined(__MasmorraDados__DungeonRoomEffect__) */
