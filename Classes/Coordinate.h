//
//  Coordinate.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__Coordinate__
#define __Tetrominos__Coordinate__

class Coordinate
{
public:
    int x;
    int y;
    
    Coordinate();
    Coordinate(int x, int y);
    
    static Coordinate add(Coordinate a, Coordinate b);
};

#endif /* defined(__Tetrominos__Coordinate__) */
