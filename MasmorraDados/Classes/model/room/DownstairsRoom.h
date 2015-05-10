//
//  DownstairsRoom.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 5/9/15.
//
//

#ifndef __MasmorraDados__DownstairsRoom__
#define __MasmorraDados__DownstairsRoom__

#include "DungeonRoom.h"

class DownstairsRoom : public DungeonRoom {
public:
  CREATE_FUNC(DownstairsRoom);
  
  virtual std::string getImagePath();
};

#endif /* defined(__MasmorraDados__DownstairsRoom__) */
