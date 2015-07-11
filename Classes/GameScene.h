//
//  GameScene.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "TetrominoBag.h"


class Tetromino;
class Grid;

class Coordinate;

class PreviewGrid;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    void setNetworkedSession(bool networkedSession);
    void receivedData(const void* data, unsigned long length);
    
protected:
    Grid* grid;
    std::unique_ptr<TetrominoBag> tetrominoBag;
    cocos2d::ui::Text* scoreLabel;
    cocos2d::ui::Text* timeLeftlabel;
    bool active;
    int totalScore;
    float stepInterval;
    float timeLeft;
    bool networkedSession;
    bool gameIsOver;
    PreviewGrid* previewGrid;
    
    //LifeCycle
    bool init() override;
    void onEnter() override;
    void setupTouchHandling();
    
    // Game Logic
    Tetromino* createRandomTetromino();
    void setGameActive(bool active);
    void step(float dt);
    void updateStateFromScore();
    void updateGameSpeed(int score);
    void gameOver();
    void update(float dt) override;
    void setTimeLeft(float time);
    
    // Networking
    void sendGameStateOverNetwork();
    
    // Utility
    Coordinate convertPositionToCoordinate(cocos2d::Vec2 position);
    
    // UI
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    void updateScoreLabel(int score);
};

#endif /* defined(__Tetrominos__GameScene__) */
