//
//  Tetromino.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__Tetromino__
#define __Tetrominos__Tetromino__

#include "cocos2d.h"
#include "Constants.h"
#include "Coordinate.h"

#define GRID_SIZE 4

class Tetromino : public cocos2d::Node
{
public:
    static Tetromino* createWithType(TetrominoType type);
    
    void rotate(bool right);
    
    int getHighestYCoordinate();
    int getWidthInBlocks();
    int getMinimumXCoordinate();
    TetrominoType getTetrominoType();
    std::vector<cocos2d::Sprite*> getBlocks();
    std::vector<int> getSkirt();
    std::vector<Coordinate> getCurrentRotations();
    cocos2d::Color3B getTetrominoColor();
    
private:
    TetrominoType type;
    std::vector<std::vector<Coordinate>> rotations;
    cocos2d::Color3B color;
    std::vector<cocos2d::Sprite*> blocks;
    int rotationIndex;
    
    bool initWithType(TetrominoType type) ;
};

#endif /* defined(__Tetrominos__Tetromino__) */
