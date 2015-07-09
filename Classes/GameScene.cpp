//
//  GameScene.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "GameScene.h"
#include "SceneManager.h"
#include "Grid.h"
#include "TetrominoBag.h"
#include "Tetromino.h"
#include "Coordinate.h"
#include "Constants.h"
#include <time.h>

using namespace cocos2d;

#pragma mark LifeCyle
bool GameScene::init()
{
    if (! Node::init()) {
        return false;
    }
    LayerColor* background = LayerColor::create(Color4B(255,255,255,255));
    this->addChild(background);
    this->tetrominoBag = std::unique_ptr<TetrominoBag>(new TetrominoBag());
    this->active = false;
    
    return true;
}

void GameScene::onEnter()
{
    Node::onEnter();
    
    cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //setup grid
    grid = Grid::create();
    
    grid->setAnchorPoint(Vec2(0.5f, 0.0f));
    grid->setPosition(Vec2(visibleSize.width * 0.5f, 0.0f));
    this->addChild(grid);
    
    //setup menu
    ui::Button* backButton = ui::Button::create();
    backButton->setAnchorPoint(Vec2(0.0f,1.0f));
    backButton->setPosition(Vec2(0.0f,visibleSize.height));
    backButton->loadTextures("backButton.png", "backButtonPressed.png");
    backButton->addTouchEventListener(CC_CALLBACK_2(GameScene::backButtonPressed,this));

    this->addChild(backButton);
    
    setupTouchHandling();
    
    this->setGameActive(true);
}

void GameScene::setupTouchHandling()
{
    auto touchListener = EventListenerTouchOneByOne::create();
    
    static Vec2 firstTouchPos;
    static Vec2 lastTouchPos;
    static bool allowRotate;
    static std::clock_t touchStartedTime;
    
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        firstTouchPos = this->convertTouchToNodeSpace(touch);
        lastTouchPos = firstTouchPos;
        allowRotate = true;
        touchStartedTime = clock();
        return true;
    };
    
    touchListener->onTouchMoved = [&](Touch* touch, Event* event)
    {
        Vec2 touchPos = this->convertTouchToNodeSpace(touch);
        
        Vec2 difference = touchPos - lastTouchPos;
        
        Tetromino* activeTetromino = grid->getActiveTetromino();
        if (activeTetromino) {
            Coordinate differenceCoordinate = this->convertPositionToCoordinate(difference);
            Coordinate activeTetrominoCoordinate = grid->getActiveTetrominoCoordinate();
            
            if (differenceCoordinate.y <= -1) {
                Coordinate newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x, activeTetrominoCoordinate.y -1);
                this->grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                lastTouchPos = touchPos;
                
                
            } else if (abs(differenceCoordinate.x) >=1) {
                Coordinate newTetrominoCoordinate;
                //we must move tetromino
                bool movingRight = (difference.x > 0);
                newTetrominoCoordinate = Coordinate(activeTetrominoCoordinate.x + (movingRight ? 1: -1), activeTetrominoCoordinate.y);
                grid->setActiveTetrominoCoordinate(newTetrominoCoordinate);
                allowRotate = false;
                lastTouchPos = touchPos;
            }
        }
    };
    
    touchListener->onTouchEnded = [&](Touch* touch, Event* event)
    {
        Vec2 touchEndPos = this->convertTouchToNodeSpace(touch);
        float distance = touchEndPos.distance(firstTouchPos);
        Size blockSize = this->grid->getBlockSize();
        
        //TODO: check the speed why is too fast
        if (distance < blockSize.width && allowRotate) {
            grid->rotateActiveTetromino();
        } else {
            Vec2 difference = touchEndPos - firstTouchPos; //maybe use lastTouchPos
            float touchDuration = (float) (clock() - touchStartedTime) /CLOCKS_PER_SEC;
            
            float velocity = fabsf(difference.y / touchDuration);

            if (velocity > DROP_VECOCITY) {
                CCLOG("DROP %f",velocity);
            }
        }
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}


#pragma mark -
#pragma mark UI Method
void GameScene::backButtonPressed(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if (eEventType == ui::Widget::TouchEventType::ENDED) {
        SceneManager::getInstance()->backToLobby();
    }
    
}
#pragma mark -
#pragma mark Public Method

#pragma mark -
#pragma mark Protected Method

Tetromino* GameScene::createRandomTetromino()
{
    TetrominoType tetrominoType = tetrominoBag->getTetromino();
    Tetromino* newTetromino = Tetromino::createWithType(tetrominoType);
    
    return newTetromino;
}

void GameScene::setGameActive(bool active)
{
    this->active = active;
    if (active) {
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::step), INITIAL_STEP_INTERVAL);
    } else {
        this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::step));
    }
}

void GameScene::step(float dt)
{
    if (! grid->getActiveTetromino()) {
        Tetromino* newTetromino = createRandomTetromino();
        this->grid->spawnTetromino(newTetromino);
    } else {
        this->grid->step();
    }
}

#pragma mark -
#pragma mark Utility Methods

Coordinate GameScene::convertPositionToCoordinate(Vec2 position)
{
    Size blockSize = grid->getBlockSize();
    return Coordinate(int(position.x/ blockSize.width), (int) position.y/blockSize.height);
}