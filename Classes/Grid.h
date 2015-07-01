//
//  Grid.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__Grid__
#define __Tetrominos__Grid__

#include <stdio.h>

class Grid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(Grid);
private:
    bool init() override;
    
};

#endif /* defined(__Tetrominos__Grid__) */
