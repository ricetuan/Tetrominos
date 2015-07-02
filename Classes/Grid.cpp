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
    this->activeTetromino = nullptr;
    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();
    
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

void Grid::spawnTetromino(Tetromino* tetromino)
{
    this->activeTetromino = tetromino;
    this->addChild(this->activeTetromino);
    
    //TODO: place tetromino in right postion
}


