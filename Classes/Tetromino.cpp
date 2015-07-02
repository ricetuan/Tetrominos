
//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"

#define GRID_SIZE 4

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
    
    this->color = tetrominoState.color;
    this->rotations = tetrominoState.rotations;
    
    this->blocks = std::vector<Sprite*>();
    this->blocks.reserve(4);
    
    this->rotationIndex = 0;
    Sprite* dummyBlock = Sprite::create("block.png");
    Size dummySize = dummyBlock->getContentSize();
    
    float gridSizeF = float(GRID_SIZE);
    this->setContentSize(Size(dummySize.width * gridSizeF, dummySize.height * gridSizeF));
    
    auto coordinates = rotations[this->rotationIndex];
    
    for (Coordinate coordinate : coordinates) {
        Sprite* block = Sprite::create("block.png");
        block->setColor(this->color);
        block->setAnchorPoint(Vec2(0.0f, 0.0f));
        block->setPosition(Vec2(coordinate.x * dummySize.width, coordinate.y * dummySize.height));
        
        this->addChild(block);
        this->blocks.push_back(block);
    }
    
    return true;
}

#pragma mark -
#pragma mark Public Methods

void Tetromino::rotate(bool right) {
    if (right) {
        rotationIndex++;
    } else {
        rotationIndex--;
    }
    
    if (rotationIndex >= (int) rotations.size()) {
        rotationIndex = 0;
    } else if (rotationIndex < 0) {
        rotationIndex = (int) rotations.size() - 1;
    }
    
    auto coordinates = rotations[this->rotationIndex];
    
    for (int index =0;index < GRID_SIZE;++index)
    {
        Sprite* block = blocks[index];
        Coordinate coordinate = coordinates[index];
        Size blockSize = block->getContentSize();
        block->setPosition(Vec2(coordinate.x * blockSize.width, coordinate.y * blockSize.height));
      
    }
    
    
    
}
