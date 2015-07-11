//
//  PreviewGrid.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/11/15.
//
//

#include "PreviewGrid.h"

using namespace cocos2d;

#pragma mark - 
#pragma mark Lifecycle

bool PreviewGrid::init()
{
    if (! Sprite::initWithFile("grid.png")) {
        return false;
    }
    return true;
}

#pragma mark -
#pragma mark Public Methods

void PreviewGrid::setState(JSONPacker::GameState state)
{
    //can be improved
    this->removeAllChildren();
    std::vector<std::vector<Color3B>> board = state.board;
    for (int column = 0; column < board.size(); ++column) {
        for (int index =0; index < board[column].size(); ++index) {
            Color3B color = board[column][index];
            
            if (!color.equals(Color3B::WHITE)) {
                Sprite* block = Sprite::create("block.png");
                Size blockSize = block->getContentSize();
                block->setColor(color);
                block->setPosition(Vec2(index * blockSize.width, column * blockSize.height));
                this->addChild(block);
            }
        }
    }
}