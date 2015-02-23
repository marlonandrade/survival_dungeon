//
//  DungeonRoomType.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 22/02/2015.
//
//

#ifndef __MasmorraDados__DungeonRoomType__
#define __MasmorraDados__DungeonRoomType__

#include "GameObject.h"

class DungeonRoomEffect;

class DungeonRoomType : public GameObject {
  CC_SYNTHESIZE(std::string, _imagePath, ImagePath);
  CC_SYNTHESIZE(std::string, _description, Description);
  CC_SYNTHESIZE(bool, _explorable, Explorable);
  CC_SYNTHESIZE(DungeonRoomEffect*, _effect, Effect);
  
public:
  CREATE_FUNC(DungeonRoomType);
};

#endif /* defined(__MasmorraDados__DungeonRoomType__) */
