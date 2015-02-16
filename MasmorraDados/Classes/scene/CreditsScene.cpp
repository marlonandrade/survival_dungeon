//
//  CreditsScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "CreditsScene.h"

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
    if (!InnerMenu::init("Creditos")) {
        return false;
    }
    
    return true;
}