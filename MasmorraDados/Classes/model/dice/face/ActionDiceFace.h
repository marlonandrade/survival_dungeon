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

class ActionDiceFace : public DiceFace
{
public:
    CREATE_FUNC(ActionDiceFace);
    
    CC_SYNTHESIZE(std::string, kind, Kind);
};

#endif /* defined(__MasmorraDados__ActionDiceFace__) */
