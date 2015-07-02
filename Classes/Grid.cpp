//
//  Grid.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Grid.h"
#include "Tetromino.h"

#pragma mark LifeCycle
bool Grid::init()
{
    if(! Sprite::initWithFile("grid.png")){
        return false;
    }
 //   Tetromino* test = Tetromino::createWithType(TetrominoType::Z);
    this->activeTetromino = nullptr;
   // this->addChild(test);
  //  test->rotate(true);
    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();
    
    this->activeTetromino = Tetromino::createWithType(TetrominoType::L);
    this->addChild(activeTetromino);
    
}

#pragma mark -
#pragma mark Public Method

void Grid::rotateActiveTetromino()
{
    if (this->activeTetromino) {
        activeTetromino->rotate(true);
    }
    
    //TODO: check if collision,undo rotation
}
