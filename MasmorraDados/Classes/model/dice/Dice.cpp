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
    auto dice = new (std::nothrow) Dice();
    if (dice && dice->initWithPlist(fileName, builder))
    {
        dice->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(dice);
    }
    
    return dice;
}

bool Dice::initWithPlist(const char* fileName, DiceFaceBuilder *builder)
{
    if (!GameObject::init())
    {
        return false;
    }
    
    auto facesData = FileUtils::getInstance()->getValueVectorFromFile(fileName);
    
    Vector<DiceFace*> faces;
    
    for (auto data : facesData)
    {
        auto faceData = data.asValueMap();
        auto face = builder->diceFace(faceData);
        face->setDice(this);
        faces.pushBack(face);
    }
    
    this->setFaces(faces);
    
    return true;
}

DiceFace* Dice::roll()
{
    return this->getFaces().getRandomObject();
}
