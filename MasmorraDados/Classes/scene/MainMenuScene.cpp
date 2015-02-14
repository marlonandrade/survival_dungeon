//
//  MainMenuScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Director *director = Director::getInstance();
    
    Size visibleSize = director->getVisibleSize();
    Vec2 visibleOrigin = director->getVisibleOrigin();
    
    Label *label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(visibleOrigin.x + visibleSize.width / 2,
                            visibleOrigin.y + visibleSize.height - 50));
    
    this->addChild(label);
    
    return true;
}