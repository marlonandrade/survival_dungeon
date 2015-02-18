//
//  MainMenuScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "MainMenuScene.h"

#include "ActionDice.h"
#include "CreditsScene.h"
#include "Definitions.h"
#include "Dice.h"
#include "DiceFace.h"
#include "Game.h"
#include "GameOptions.h"
#include "OptionsScene.h"
#include "RulesScene.h"

USING_NS_CC;

#pragma mark - Private Interface

Menu* MainMenu::createMenu()
{
    Vector<MenuItem*> menuItems;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
    
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/farcry.ttf";
    labelConfig.fontSize = 32 * scaleFactor;
    
    auto iniciarLabel = Label::createWithTTF(labelConfig, "INICIAR");
    auto iniciarMenuItem = MenuItemLabel::create(iniciarLabel, [&](Ref* sender) {
        Game* game = Game::create();
        auto options = game->getOptions();
        
        log("%d", options->requiredXpToWin);
        
        options->requiredXpToWin = 21;
        
        log("%d", options->requiredXpToWin);
    
        log("Iniciar touched");
    });
    menuItems.pushBack(iniciarMenuItem);
    
    auto rulesLabel = Label::createWithTTF(labelConfig, "REGRAS");
    auto rulesMenuItem = MenuItemLabel::create(rulesLabel, [&](Ref* sender) {
        auto rulesScene = Rules::createScene();
        Director::getInstance()->pushScene(rulesScene);
    });
    menuItems.pushBack(rulesMenuItem);
    
    auto optionsLabel = Label::createWithTTF(labelConfig, "OPCOES");
    auto optionsMenuItem = MenuItemLabel::create(optionsLabel, [&](Ref* sender) {
        auto optionsScene = Options::createScene();
        Director::getInstance()->pushScene(optionsScene);
    });
    menuItems.pushBack(optionsMenuItem);
    
    auto creditsLabel = Label::createWithTTF(labelConfig, "CREDITOS");
    auto creditsMenuItem = MenuItemLabel::create(creditsLabel, [&](Ref* sender) {
        auto creditsScene = Credits::createScene();
        Director::getInstance()->pushScene(creditsScene);
    });
    menuItems.pushBack(creditsMenuItem);
    
    float margin = visibleSize.height / 8;
    ssize_t size = menuItems.size();
    for (int i = 0; i < size; i++) {
        auto menuItem = menuItems.at(i);
        menuItem->setPositionY(margin/2 + ((size - i - 3) * margin));
    }
    
    return Menu::createWithArray(menuItems);
}

LayerColor* MainMenu::getConfirmQuitLayer()
{
    if (!_confirmQuitLayer) {
        _confirmQuitLayer = LayerColor::create(Color4B(0, 0, 0, 200));
        CC_SAFE_RETAIN(_confirmQuitLayer);
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
        
        float scaleFactor = visibleSize.width / FONT_SCALE_RATIO;
        float centerX = visibleSize.width / 2 + visibleOrigin.x;
        float centerY = visibleSize.height / 2 + visibleOrigin.y;
        
        TTFConfig labelConfig;
        labelConfig.fontFilePath = "fonts/farcry.ttf";
        labelConfig.fontSize = 45 * scaleFactor;
        
        auto questionLabel = Label::createWithTTF(labelConfig, "DESEJA REALMENTE SAIR?");
        
        labelConfig.fontSize = 38 * scaleFactor;
        
        Vector<MenuItem*> menuItems;
        auto yesLabel = Label::createWithTTF(labelConfig, "SIM");
        auto yesMenuItem = MenuItemLabel::create(yesLabel, [](Ref* sender) {
            Director::getInstance()->end();
        });
        yesMenuItem->setPosition(Vec2(-80 * scaleFactor, 0));
        
        auto noLabel = Label::createWithTTF(labelConfig, "NAO");
        auto noMenuItem = MenuItemLabel::create(noLabel, [&](Ref *sender) {
            _confirmQuitLayer->removeFromParent();
        });
        noMenuItem->setPosition(Vec2(80 * scaleFactor, 0));
        
        menuItems.pushBack(yesMenuItem);
        menuItems.pushBack(noMenuItem);
        
        auto menu = Menu::createWithArray(menuItems);
        
        questionLabel->setPosition(Vec2(centerX, centerY + 50 * scaleFactor));
        menu->setPosition(Vec2(centerX, centerY - 50 * scaleFactor));
        
        _confirmQuitLayer->addChild(questionLabel);
        _confirmQuitLayer->addChild(menu);
    }
    
    return _confirmQuitLayer;
}

#pragma mark - Public Interface

Scene* MainMenu::createScene()
{
    auto scene = Scene::create();
    auto layer = MainMenu::create();
    scene->addChild(layer);
    return scene;
}

bool MainMenu::init()
{
    if (!BaseMenu::init("Menu Inicial")) {
        return false;
    }
    
    Director *director = Director::getInstance();
    
    Size visibleSize = director->getVisibleSize();
    Vec2 visibleOrigin = director->getVisibleOrigin();
    
    float centerX = visibleOrigin.x + visibleSize.width / 2;
    float centerY = visibleOrigin.y + visibleSize.height / 2;
    
    auto menu = this->createMenu();
    menu->setPosition(Vec2(centerX,
                           centerY));
    
    this->addChild(menu);
    
    auto* actionDice = ActionDice::create();
    
    return true;
}

void MainMenu::leave()
{
    if (!getConfirmQuitLayer()->getParent()) {
        this->addChild(getConfirmQuitLayer());
    }
}