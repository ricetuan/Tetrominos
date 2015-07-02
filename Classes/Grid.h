//
//  Grid.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include "cocos2d.h"

class Tetromino;

class Grid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Grid);
    
    void rotateActiveTetromino();
    
private:
    Tetromino* activeTetromino;
    
    bool init() override;
    void onEnter() override;
    
};

#endif /* defined(__Tetrominos__Grid__) */
