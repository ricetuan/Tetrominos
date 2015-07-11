//
//  Grid.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include "cocos2d.h"
#include "Coordinate.h"

class Tetromino;

class Grid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Grid);
    
    void rotateActiveTetromino();
    void spawnTetromino(Tetromino* tetromino);
    void step();
    void setActiveTetrominoCoordinate(Coordinate coordinate);
    Coordinate getActiveTetrominoCoordinate();
    cocos2d::Size getBlockSize();
    Tetromino* getActiveTetromino();
    void dropActiveTetromino();
    int getScore();
    int getTotalLineCleared();
    bool checkIfTopReached();
    std::vector<std::vector<cocos2d::Sprite*>> getBlocksLanded();
    
private:
    Tetromino* activeTetromino;
    Tetromino* ghostTetromino;
    Coordinate activeTetrominoCoordinate;
    std::vector<std::vector<cocos2d::Sprite*>> blocksLanded;
    int score;
    int totalLinesCleared;

    bool init() override;
    void onEnter() override;
    cocos2d::Vec2 convertCoordinateToPosition(Coordinate coordinate);
    bool checkIFTetrominoCollides(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void deactiveTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    void placeTetrominoOnBorad(Tetromino* tetromino, Coordinate tetrominoCoordinate);
    Coordinate getTetrominoLandingCoordinate();
    void updateGhostTetrominoPosition();
    void updateScore(int lineCleared);
    
    void clearLines();

};

#endif /* defined(__Tetrominos__Grid__) */
