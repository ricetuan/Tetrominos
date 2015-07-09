//
//  Grid.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Grid.h"
#include "Tetromino.h"
using namespace cocos2d;

#pragma mark LifeCycle
bool Grid::init()
{
    if(! Sprite::initWithFile("grid.png")){
        return false;
    }
    this->activeTetromino = nullptr;
    this->activeTetrominoCoordinate = Coordinate();
    return true;
}

void Grid::onEnter()
{
    Sprite::onEnter();
    
}

#pragma mark -
#pragma mark Public Methods

void Grid::rotateActiveTetromino()
{
    if (this->activeTetromino) {
        activeTetromino->rotate(true);
        if (this->checkIFTetrominoCollides(activeTetromino, activeTetrominoCoordinate)) {
            this->activeTetromino->rotate(false);
        }
            
    }
    
    //TODO: check if collision,undo rotation
}

void Grid::spawnTetromino(Tetromino* tetromino)
{
    this->activeTetromino = tetromino;

    this->activeTetromino->setAnchorPoint(Vec2(0.0f, 0.0f));
    
    int width = this->activeTetromino->getWidthInBlocks();
    int highestY = this->activeTetromino->getHighestYCoordinate();
    
    Coordinate spawnCoordinate = Coordinate(GRID_WIDTH/2 - width/2 - 1,GRID_HEIGHT - highestY - 1);
    
    this->setActiveTetrominoCoordinate(spawnCoordinate);
    
    this->addChild(this->activeTetromino);
}

void Grid::step()
{
    Coordinate activeCoordinate = this->getActiveTetrominoCoordinate();
    Coordinate nextCoordinate = Coordinate(activeCoordinate.x, activeCoordinate.y -1);
    
    this->setActiveTetrominoCoordinate(nextCoordinate);
}



#pragma mark -
#pragma mark Setters / Getters
void Grid::setActiveTetrominoCoordinate(Coordinate coordinate)
{
    if (activeTetromino) {
        if (! this->checkIFTetrominoCollides(activeTetromino, coordinate)) {
             activeTetrominoCoordinate = coordinate;
             activeTetromino->setPosition(this->convertCoordinateToPosition(activeTetrominoCoordinate));
        }
    }
 
}

Tetromino* Grid::getActiveTetromino()
{
    return this->activeTetromino;
}

Coordinate Grid::getActiveTetrominoCoordinate()
{
    return this->activeTetrominoCoordinate;
}

Size Grid::getBlockSize()
{
    Size contentSize = this->getContentSize();

    float blockWidth = contentSize.width / float(GRID_WIDTH);
    float blockHeight = contentSize.height/ float(GRID_HEIGHT);
    
    return Size(blockWidth,blockHeight);
}


#pragma mark -
#pragma mark Private Methods

Vec2 Grid::convertCoordinateToPosition(Coordinate coordinate)
{
    Size contentSize = this->getContentSize();
    
    float blockWidth = contentSize.width / float(GRID_WIDTH);
    float blockHeight = contentSize.height/ float(GRID_HEIGHT);
    
    return Vec2(coordinate.x * blockWidth,coordinate.y * blockHeight);
    
}

bool Grid::checkIFTetrominoCollides(Tetromino* tetromino, Coordinate tetrominoCoordinate)
{
    int skirtStart = tetromino->getMinimumXCoordinate();
    std::vector<int> skirt = tetromino->getSkirt();
    for (int index=0; index < skirt.size(); ++index) {
        Coordinate localCoordinate = Coordinate(index + skirtStart, skirt[index]);
        Coordinate gridCoordinate = Coordinate::add(tetrominoCoordinate, localCoordinate);
        
        if (gridCoordinate.x < 0 || gridCoordinate.y < 0 || gridCoordinate.x >= GRID_WIDTH || gridCoordinate.y >= GRID_HEIGHT) {
            return true;
        }
    }
    return false;
}


