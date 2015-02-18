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
    
    virtual std::string getKind() const;
    virtual void setKind(std::string kind);
private:
    std::string _kind;
};

#endif /* defined(__MasmorraDados__ActionDiceFace__) */
