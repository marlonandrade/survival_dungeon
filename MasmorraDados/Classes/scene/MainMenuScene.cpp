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
    
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/farcry.ttf";
    labelConfig.fontSize = 40;
    
    auto iniciarLabel = Label::createWithTTF(labelConfig, "INICIAR");
    auto iniciarMenuItem = MenuItemLabel::create(iniciarLabel, [](Ref* sender) {
        log("Iniciar touched");
    });
    menuItems.pushBack(iniciarMenuItem);
    
    auto rulesLabel = Label::createWithTTF(labelConfig, "REGRAS");
    auto rulesMenuItem = MenuItemLabel::create(rulesLabel, [](Ref* sender) {
        log("Regras touched");
    });
    menuItems.pushBack(rulesMenuItem);
    
    auto optionsLabel = Label::createWithTTF(labelConfig, "OPCOES");
    auto optionsMenuItem = MenuItemLabel::create(optionsLabel, [](Ref* sender) {
        log("Opções touched");
    });
    menuItems.pushBack(optionsMenuItem);
    
    auto creditsLabel = Label::createWithTTF(labelConfig, "CREDITOS");
    auto creditsMenuItem = MenuItemLabel::create(creditsLabel, [](Ref* sender) {
        log("Créditos touched");
    });
    menuItems.pushBack(creditsMenuItem);
    
    float margin = 100;
    int size = menuItems.size();
    for (int i = 0; i < size; i++) {
        auto menuItem = menuItems.at(i);
        menuItem->setPositionY(margin/2 + ((size - i - 3) * margin));
    }
    
    return Menu::createWithArray(menuItems);
}