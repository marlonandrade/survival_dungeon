//
//  IntroScene.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 14/02/2015.
//
//

#include "IntroScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* Intro::createScene()
{
    auto scene = Scene::create();
    auto layer = Intro::create();
    scene->addChild(layer);
    return scene;
}

void Intro::transitionToMainMenu(float deltaTime)
{
    Scene *mainMenuScene = MainMenu::createScene();
    Director::getInstance()->replaceScene(mainMenuScene);
}

bool Intro::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    Director *director = Director::getInstance();
    
    Size visibleSize = director->getVisibleSize();
    Vec2 visibleOrigin = director->getVisibleOrigin();
    
    Vec2 center = Vec2(visibleSize.width / 2 + visibleOrigin.x,
                       visibleSize.height / 2 + visibleOrigin.y);
    
    Sprite *introImage = Sprite::create("images/intro.jpg");
    introImage->setContentSize(visibleSize);
    introImage->setPosition(center);
    
    this->addChild(introImage, 0);
    
    this->schedule(schedule_selector(Intro::transitionToMainMenu), 3);
    
    return true;
}