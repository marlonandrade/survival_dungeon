//
//  RulesScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "RulesScene.h"
#include "BackMenu.h"

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
    if (!BaseMenu::init("Regras")) {
        return false;
    }
    
    this->addChild(BackMenu::createMenu());
    
    return true;
}