//
//  ActionDiceFaceBuilder.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "ActionDiceFaceBuilder.h"

#include "ActionDiceFace.h"

DiceFace* ActionDiceFaceBuilder::diceFace(cocos2d::ValueMap &map)
{
    auto face = ActionDiceFace::create();
    face->setImageName(map.at("image").asString());
    face->setKind(map.at("kind").asString());
    return face;
}