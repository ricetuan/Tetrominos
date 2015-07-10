
//
//  Tetromino.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Tetromino.h"
#include "JSONPacker.h"
#include <unordered_set>

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
    
    auto coordinates = this->getCurrentRotations();
    
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
    
    auto coordinates = this->getCurrentRotations();
    
    for (int index =0;index < GRID_SIZE;++index)
    {
        Sprite* block = blocks[index];
        Coordinate coordinate = coordinates[index];
        Size blockSize = block->getContentSize();
        block->setPosition(Vec2(coordinate.x * blockSize.width, coordinate.y * blockSize.height));
      
    }
    
}

int Tetromino::getHighestYCoordinate()
{
    auto coordinates = this->getCurrentRotations();
    int highestYCoordinate = 0;

    for (Coordinate coordinate : coordinates) {
        highestYCoordinate = highestYCoordinate >= coordinate.y ? highestYCoordinate : coordinate.y;
    }
    return highestYCoordinate;
}

int Tetromino::getWidthInBlocks()
{
    auto coordinates = this->getCurrentRotations();
    std::unordered_set<int> widthPoint;
    for (Coordinate coordinate : coordinates) {
        widthPoint.insert(coordinate.x);
    }
    return widthPoint.size();
}

int Tetromino::getMinimumXCoordinate()
{
    auto coordinates = this->getCurrentRotations();
    int mininumXCoordinate = GRID_SIZE;
    for (Coordinate coordinate : coordinates) {
        mininumXCoordinate = coordinate.x < mininumXCoordinate ? coordinate.x : mininumXCoordinate;
    }
    return mininumXCoordinate;
}

std::vector<int> Tetromino::getSkirt()
{
    int width = this->getWidthInBlocks();
    int skirtStart = this->getMinimumXCoordinate();
    
    std::vector<int> skirt = std::vector<int>(width,GRID_SIZE -1);
    
    auto coordinates = this->getCurrentRotations();
    for (Coordinate coordinate : coordinates) {
        int x = coordinate.x - skirtStart;
        int skirtY = skirt[x];
        
        if (coordinate.y < skirtY) {
            skirt[x] = coordinate.y;
        }
    }
    return skirt;

}

std::vector<Sprite*> Tetromino::getBlocks()
{
    return blocks;
}

std::vector<Coordinate> Tetromino::getCurrentRotations()
{
    return rotations[rotationIndex];
}

TetrominoType Tetromino::getTetrominoType()
{
    return this->type;
}