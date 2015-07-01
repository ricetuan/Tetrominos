
//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Tetromino.h"

Tetromino* Tetromino::createWithType(TetrominoType type)
{
    Tetromino* tetromino = new (std::nothrow) Tetromino();
    if (tetromino && tetromino->initWithType(type)) {
        tetromino->autorelease();
        return tetromino;
    } else {
        CC_SAFE_DELETE(tetromino);
        return nullptr;        
    }
}



bool Tetromino::initWithType(TetrominoType type)
{
    if (! Node::init()) {
        return false;
    }
    
    this->type = type;
    rotations = std::vector<std::vector<Coordinate>>();
    
    return true;
}
