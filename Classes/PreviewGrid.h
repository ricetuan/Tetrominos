//
//  PreviewGrid.h
//  Tetrominos
//
//  Created by Liang Fan on 7/11/15.
//
//

#ifndef __Tetrominos__PreviewGrid__
#define __Tetrominos__PreviewGrid__

#include "cocos2d.h"
#include "JSONPacker.h"

class PreviewGrid : public cocos2d::Sprite
{
public:
    CREATE_FUNC(PreviewGrid);
    void setState(JSONPacker::GameState state);
private:
    bool init() override;
};
#endif /* defined(__Tetrominos__PreviewGrid__) */
