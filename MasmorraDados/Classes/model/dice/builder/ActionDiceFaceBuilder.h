//
//  ActionDiceFaceBuilder.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__ActionDiceFaceBuilder__
#define __MasmorraDados__ActionDiceFaceBuilder__

#include "DiceFaceBuilder.h"

class ActionDiceFaceBuilder : public DiceFaceBuilder
{
public:
    CREATE_FUNC(ActionDiceFaceBuilder);
    virtual DiceFace* diceFace(cocos2d::ValueMap &map);
};

#endif /* defined(__MasmorraDados__ActionDiceFaceBuilder__) */
