//
//  Grid.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "Grid.h"
#include "Tetromino.h"

bool Grid::init()
{
    if(! Sprite::initWithFile("grid.png")){
        return false;
    }
    return true;
}
