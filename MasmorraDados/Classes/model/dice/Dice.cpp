//
//  Dice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dice.h"
#include "DiceFace.h"
#include "DiceFaceBuilder.h"

USING_NS_CC;

Dice* Dice::createWithPlist(const char* fileName, DiceFaceBuilder *builder)
{
    Dice *dice = new (std::nothrow) Dice();
    dice->initWithPlist(fileName, builder);
    dice->autorelease();
    return dice;
}

bool Dice::initWithPlist(const char* fileName, DiceFaceBuilder *builder)
{
    auto facesData = FileUtils::getInstance()->getValueVectorFromFile(fileName);
    
    Vector<DiceFace*> faces;
    
    for(auto it = facesData.begin(); it != facesData.end(); ++it) {
        auto faceData = it->asValueMap();
        auto face = builder->diceFace(faceData);
        faces.pushBack(face);
    }
    
    _faces = faces;
    
    return true;
}

DiceFace* Dice::roll()
{
    return _faces.getRandomObject();
}