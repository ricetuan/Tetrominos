//
//  GameScene.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__GameScene__
#define __Tetrominos__GameScene__
#include "CocosGUI.h"

class Grid;

class GameScene : public cocos2d::Node
{
public:
    CREATE_FUNC(GameScene);
    
protected:
    Grid* grid;
    
    bool init() override;
    void onEnter() override;
    void backButtonPressed(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    
    void setupTouchHandling();
};

#endif /* defined(__Tetrominos__GameScene__) */
