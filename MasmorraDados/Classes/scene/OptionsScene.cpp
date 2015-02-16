//
//  OptionsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "OptionsScene.h"

USING_NS_CC;

Scene* Options::createScene()
{
    auto scene = Scene::create();
    auto layer = Options::create();
    scene->addChild(layer);
    return scene;
}

bool Options::init()
{
    if (!InnerMenu::init("Opcoes")) {
        return false;
    }
    
    return true;
}