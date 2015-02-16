//
//  CreditsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "CreditsScene.h"
#include "BackMenu.h"

USING_NS_CC;

Scene* Credits::createScene()
{
    auto scene = Scene::create();
    auto layer = Credits::create();
    scene->addChild(layer);
    return scene;
}

bool Credits::init()
{
    if (!BaseMenu::init("Creditos")) {
        return false;
    }
    
    this->addChild(BackMenu::createMenu());
    
    return true;
}