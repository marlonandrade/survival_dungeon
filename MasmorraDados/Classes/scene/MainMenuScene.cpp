//
//  MainMenuScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "MainMenuScene.h"
#include <CCMenuItem.h>

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
    
    float centerX = visibleOrigin.x + visibleSize.width / 2;
    float centerY = visibleOrigin.y + visibleSize.height / 2;
    
    Label *label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2(centerX,
                            visibleOrigin.y + visibleSize.height - 50));
    
    auto menu = this->createMenu();
    menu->setPosition(Vec2(centerX,
                           centerY));
    
    this->addChild(menu);
    this->addChild(label);
    
    return true;
}

Menu* MainMenu::createMenu()
{
    Vector<MenuItem*> menuItems;
    
    float margin = 80;
    
    auto iniciarMenuItem = MenuItemFont::create("Iniciar", [](Ref* sender) {
        log("Iniciar touched");
    });
    iniciarMenuItem->setPositionY(-margin/2 - margin);
    menuItems.pushBack(iniciarMenuItem);
    
    auto rulesMenuItem = MenuItemFont::create("Regras", [](Ref* sender) {
        log("Regras touched");
    });
    rulesMenuItem->setPositionY(-margin/2);
    menuItems.pushBack(rulesMenuItem);
    
    auto optionsMenuItem = MenuItemFont::create("Opções", [](Ref* sender) {
        log("Opções touched");
    });
    optionsMenuItem->setPositionY(margin/2);
    menuItems.pushBack(optionsMenuItem);
    
    auto creditsMenuItem = MenuItemFont::create("Créditos", [](Ref* sender) {
        log("Créditos touched");
    });
    creditsMenuItem->setPositionY(margin/2 + margin);
    menuItems.pushBack(creditsMenuItem);
    
    return Menu::createWithArray(menuItems);
}