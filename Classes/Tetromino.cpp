
//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"
using namespace cocos2d;

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
    
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile("tetrominos.json");
    JSONPacker::TetrominoState tetrominoState = JSONPacker::unpackTetrominoJSON(jsonStr, type);
    
    return true;
}
