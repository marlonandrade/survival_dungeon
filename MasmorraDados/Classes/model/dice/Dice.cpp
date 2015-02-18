//
//  Dice.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 18/02/2015.
//
//

#include "Dice.h"

USING_NS_CC;

Dice* Dice::createWithPlist(const char* fileName)
{
    Dice *dice = new (std::nothrow) Dice();
    dice->initWithPlist(fileName);
    dice->autorelease();
    return dice;
}

bool Dice::initWithPlist(const char* fileName)
{
    auto facesData = FileUtils::getInstance()->getValueVectorFromFile(fileName);
    
    for(auto it = facesData.begin(); it != facesData.end(); ++it) {
        auto faceData = it->asValueMap();
        log("%s", faceData.at("image").asString().c_str());
        log("%s", faceData.at("name").asString().c_str());
    }
    
    return true;
}

DiceFace* Dice::roll()
{
    assert("roll must be overriden");
    return nullptr;
}