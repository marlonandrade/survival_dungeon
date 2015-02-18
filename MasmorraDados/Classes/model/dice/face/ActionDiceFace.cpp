//
//  ActionDiceFace.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDiceFace.h"

#pragma mark - Getter

std::string ActionDiceFace::getKind() const
{
    return _kind;
}

#pragma mark - Setter

void ActionDiceFace::setKind(std::string kind)
{
    _kind = kind;
}