//
//  JSONPacker.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__JSONPacker__
#define __Tetrominos__JSONPacker__

#include "cocos2d.h"
#include "Coordinate.h"
#include "Constants.h"

namespace JSONPacker
{
    struct TetrominoState
    {
        cocos2d::Color3B color;
        std::vector<std::vector<Coordinate>> rotations;
    };
    
    struct GameState
    {
        std::string name;
        bool gameOver;
        int score;
        std::vector<std::vector<cocos2d::Color3B>> board;
    };
    
    GameState unpackGameStateJSON(std::string json);
    std::string packGameStateJSON(const GameState data);
    
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type);
}

#endif /* defined(__Tetrominos__JSONPacker__) */
