//
//  DiceFace.h
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#ifndef __MasmorraDados__DiceFace__
#define __MasmorraDados__DiceFace__

#include "GameObject.h"

class DiceFace : public GameObject
{
public:
    CREATE_FUNC(DiceFace);
    
    virtual std::string getImageName() const;
    virtual void setImageName(std::string imageName);
private:
    std::string _imageName;
};

#endif /* defined(__MasmorraDados__DiceFace__) */
