//
//  DiceFace.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "DiceFace.h"

#pragma mark - Getter

std::string DiceFace::getImageName() const
{
    return _imageName;
}

#pragma mark - Setter

void DiceFace::setImageName(std::string imageName)
{
    _imageName = imageName;
}