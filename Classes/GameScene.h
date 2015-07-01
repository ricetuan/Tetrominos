//
//  GameScene.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    
protected:
    bool init() override;
};

#endif /* defined(__Tetrominos__GameScene__) */
