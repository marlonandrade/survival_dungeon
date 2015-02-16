//
//  OptionsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "OptionsScene.h"
#include "BackMenu.h"

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
    if (!BaseMenu::init("Opcoes")) {
        return false;
    }
    
    this->addChild(BackMenu::createMenu());
    
    return true;
}