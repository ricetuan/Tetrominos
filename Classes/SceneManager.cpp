//
//  SceneManager.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "SceneManager.h"
#include "cocos2d.h"
#include "GameScene.h"
using namespace cocos2d;

#pragma mark - 
#pragma mark Lifecycle

static SceneManager* sharedSceneManager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (! sharedSceneManager) {
        sharedSceneManager = new (std::nothrow) SceneManager();
    }
       return sharedSceneManager;
}

SceneManager::SceneManager()
{
    this->networkingWrapper = std::unique_ptr<NetworkingWrapper>(new NetworkingWrapper());
    this->networkingWrapper->setDelegate(this);
}


SceneManager::~SceneManager()
{
    
}

#pragma mark -
#pragma makr Public Methods
void SceneManager::enterGameScene(bool networked)
{
    Scene* scene = Scene::create();
    GameScene* gameScene = GameScene::create();
    gameScene->setNetworkedSession(networked);
    
    scene->addChild(gameScene);
    
    Director::getInstance()->pushScene(scene);
}

void SceneManager::backToLobby()
{
    Director::getInstance()->popScene();
}

void SceneManager::showPeerList()
{
    networkingWrapper->showPeerList();
}

void SceneManager::receiveMultiplayerInvitations()
{
    networkingWrapper->startAdvertisingAvailability();
}

#pragma mark -
#pragma mark NetworkingWapperDelegate Methods

void SceneManager::receivedData(const void *data, unsigned long length)
{
    
}

void SceneManager::stateChanged(ConnectionState state)
{
    switch (state) {
        case ConnectionState::CONNECTING:
            CCLOG("Connecting..");
            break;
        case ConnectionState::NOT_CONNECTED:
            CCLOG("Not Connected");
            break;
        case ConnectionState::CONNECTED:
            CCLOG("Connected");
            break;
    }
}