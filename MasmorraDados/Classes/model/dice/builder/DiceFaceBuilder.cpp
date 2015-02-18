//
//  DiceFaceBuilder.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "DiceFaceBuilder.h"

#include "DiceFace.h"

DiceFace* DiceFaceBuilder::diceFace(cocos2d::ValueMap &map)
{
    auto face = DiceFace::create();
    face->setImageName(map.at("image").asString());
    return face;
}