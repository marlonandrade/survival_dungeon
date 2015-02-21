//
//  NewGameScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "NewGameScene.h"

USING_NS_CC;

Scene* NewGameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = NewGameScene::create();
    scene->addChild(layer);
    return scene;
}

bool NewGameScene::init()
{
    if (!InnerMenu::init("NOVO JOGO"))
    {
        return false;
    }
    
    return true;
}