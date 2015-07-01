//
//  Lobby.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Lobby.h"

using namespace cocos2d;

bool Lobby::init()
{
    if (! Node::init()) {
        return false;
    }
    
    LayerColor* background = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(background);
    
    return true;
}

void Lobby::onEnter()
{
    Node::onEnter();
    setupUI();
}

void Lobby::setupUI()
{
    Size visiableSize = Director::getInstance()->getVisibleSize();
    Sprite* logo = Sprite::create("logo.png");
    logo->setPosition(Vec2(visiableSize.width/2.0f,visiableSize.height*0.7f));
    this->addChild(logo);

    ui::Button* singlePlayerButton = ui::Button::create();
    singlePlayerButton->setPosition(Vec2(visiableSize.width/2.0f,visiableSize.height * 0.4f));
    singlePlayerButton->loadTextures("singlePlayerButton.png", "singlePlayerButtonPressed.png");
    this->addChild(singlePlayerButton);
    
    ui::Button* multiPlayerButton = ui::Button::create();
    multiPlayerButton->setPosition(Vec2(visiableSize.width/2.0f,visiableSize.height * 0.25f));
    multiPlayerButton->loadTextures("multiplayerButton.png", "multiplayerButtonPressed.png");
    this->addChild(multiPlayerButton);
    
    singlePlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::SinglePlayerPressed,this));
    multiPlayerButton->addTouchEventListener(CC_CALLBACK_2(Lobby::multiplayerPressed, this));
}

void Lobby::SinglePlayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        
    }
    CCLOG("1 player");
}


void Lobby::multiplayerPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    CCLOG("2 player");

}