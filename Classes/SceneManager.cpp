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
    scene->addChild(gameScene);
    
    Director::getInstance()->pushScene(scene);
}
