//
//  ActionDiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__ActionDiceFace__
#define __MasmorraDados__ActionDiceFace__

#include "DiceFace.h"

class ActionDiceFace : public DiceFace {
  CC_SYNTHESIZE(std::string, _kind, Kind);
  
public:
  CREATE_FUNC(ActionDiceFace);
};

#endif /* defined(__MasmorraDados__ActionDiceFace__) */
