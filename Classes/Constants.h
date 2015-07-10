//
//  Constants.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef Tetrominos_Constants_h
#define Tetrominos_Constants_h

static const int GRID_WIDTH = 10;
static const int GRID_HEIGHT = 20;

static const float INITIAL_STEP_INTERVAL = 1.0f;
static const int SCORE_TO_ACCELERATE = 1;
static const float ACCELERATION_FACTOR = 0.9f;
static const float DROP_VECOCITY = 10000.0f;
static const float SPEED_MAX = 0.1f;

static const int BLOCKS_PER_TETROMINO = 4;


enum class TetrominoType {
    I = 0,
    O = 1,
    T = 2,
    S = 3,
    Z = 4,
    J = 5,
    L = 6
};

#endif
