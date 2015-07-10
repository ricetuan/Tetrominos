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
    
    for (int index = 0; index < GRID_HEIGHT; ++index) {
        std::vector<Sprite*> row(GRID_WIDTH,nullptr);
        blocksLanded.push_back(row);
    }
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
    if (activeTetromino) {
        
        Coordinate activeCoordinate = this->getActiveTetrominoCoordinate();
        Coordinate nextCoordinate = Coordinate(activeCoordinate.x, activeCoordinate.y -1);
    
        if (checkIFTetrominoCollides(activeTetromino, nextCoordinate)) {
            deactiveTetromino(activeTetromino, activeTetrominoCoordinate);
        } else {
            this->setActiveTetrominoCoordinate(nextCoordinate);
        }
    }
    
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
        
        if (blocksLanded[gridCoordinate.y][gridCoordinate.x]) {
            return true;
        }
    }
    return false;
}

void Grid::deactiveTetromino(Tetromino* tetromino, Coordinate tetrominoCoordinate)
{
    this->placeTetrominoOnBorad(tetromino, tetrominoCoordinate);
    this->activeTetromino->removeFromParent();
    this->activeTetromino = nullptr;
    clearLines();
}

void Grid::placeTetrominoOnBorad(Tetromino* tetromino, Coordinate tetrominoCoordinate)
{
    std::vector<Sprite*> blocks = tetromino->getBlocks();
    std::vector<Coordinate> coordinates = tetromino->getCurrentRotations();
    for (int index = 0 ; index < BLOCKS_PER_TETROMINO; ++index) {
        //get tetromino coordinate
        Coordinate localCoordinate = coordinates[index];
        Coordinate gridCoordinate = Coordinate::add(tetrominoCoordinate,localCoordinate);
        
        Sprite* block = blocks[index];
        
      // or  Vec2 gridPosition = convertCoordinateToPosition(gridCoordinate);
        Vec2 gridPosition = block->getPosition() + tetromino->getPosition();
        
        block->retain();
        block->removeFromParent();
        
        this->addChild(block);
        block->release();
        
        block->setPosition(gridPosition);
        blocksLanded[gridCoordinate.y][gridCoordinate.x] = block;
        
    }
    
}

Coordinate Grid::getTetrominoLandingCoordinate()
{
    Coordinate landingTetrominoCoordinate = activeTetrominoCoordinate;
    while (! checkIFTetrominoCollides(activeTetromino, landingTetrominoCoordinate)) {
        landingTetrominoCoordinate.y--;
    }
    landingTetrominoCoordinate.y++;
    return landingTetrominoCoordinate;
}

void Grid::dropActiveTetromino()
{
        Coordinate landingCoordinate = this->getTetrominoLandingCoordinate();
        this->setActiveTetrominoCoordinate(landingCoordinate);
        this->deactiveTetromino(activeTetromino, activeTetrominoCoordinate);

}

void Grid::clearLines()
{
    for(int y=0;y<GRID_HEIGHT;++y)
    {
        //check if all the blocks in a row are filled
        bool fullLine = true;
        std::vector<Sprite*> row = blocksLanded[y];
        
        for (auto block : row) {
            if (!block) {
                fullLine = false;
                break;
            }
        }
        
        //clear teh line if filled
        if (fullLine) {
            for (Sprite* block : row)
            {
                block->removeFromParent();
            }
            blocksLanded.erase(blocksLanded.begin() + y);
            
            std::vector<std::vector<Sprite*>> rowsToMoveDown(blocksLanded.begin() + y,blocksLanded.end());
            
            for (std::vector<Sprite*> rowAbove : rowsToMoveDown) {
                for (Sprite* block : rowAbove) {
                    if (block) {
                        block->setPositionY(block->getPosition().y - block->getContentSize().height);
                    }
                }
            }
            y--;
        }
        
        std::vector<Sprite*> newRow(GRID_WIDTH, nullptr);
        blocksLanded.push_back(newRow);

        //move bloks in all rows above down one y coordinate
    }
}


