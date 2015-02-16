//
//  RulesScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "RulesScene.h"

USING_NS_CC;

Scene* Rules::createScene()
{
    auto scene = Scene::create();
    auto layer = Rules::create();
    scene->addChild(layer);
    return scene;
}

bool Rules::init()
{
    if (!InnerMenu::init("Regras")) {
        return false;
    }
    
    return true;
}