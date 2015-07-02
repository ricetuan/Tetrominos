//
//  TetrominoBag.h
//  Tetrominos
//
//  Created by Liang Fan on 7/3/15.
//
//

#ifndef __Tetrominos__TetrominoBag__
#define __Tetrominos__TetrominoBag__

#include <stdio.h>
#include "Constants.h"

class TetrominoBag
{
public:
    TetrominoBag();
    
    TetrominoType getTetromino();

private:
    std::vector<TetrominoType> bag;
    std::default_random_engine randomGenerator;
    
};
#endif /* defined(__Tetrominos__TetrominoBag__) */
