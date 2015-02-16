//
//  InnerMenuLayer.cpp
//  MasmorraDados
//
//  Created by Marlon Andrade on 16/02/2015.
//
//

#include "InnerMenuLayer.h"
#include "Definitions.h"
#include "BackMenu.h"

USING_NS_CC;

bool InnerMenu::init(std::string title)
{
    if (!BaseMenu::init(title)) {
        return false;
    }
    
    this->addChild(BackMenu::createMenu());
    
    return true;
}


#pragma mark - Layer overriden methods

void InnerMenu::onEnter()
{
    Layer::onEnter();
    
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyReleased = CC_CALLBACK_2(InnerMenu::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void InnerMenu::onExit()
{
    _eventDispatcher->removeEventListenersForTarget(this);
    
    Layer::onExit();
}

void InnerMenu::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ||
        keyCode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
        Director::getInstance()->popScene();
    }
}