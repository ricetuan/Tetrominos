//
//  JSONPacker.cpp
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#include "JSONPacker.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Constants.h"

using namespace cocos2d;

namespace JSONPacker {
    TetrominoState unpackTetrominoJSON(std::string json, TetrominoType type)
    {
        rapidjson::Document document;
        document.Parse<0>(json.c_str());
        
        const char* typeStr;
        switch (type) {
            case TetrominoType::I: typeStr = "I"; break;
            case TetrominoType::O: typeStr = "O"; break;
            case TetrominoType::T: typeStr = "T"; break;
            case TetrominoType::S: typeStr = "S"; break;
            case TetrominoType::Z: typeStr = "Z"; break;
            case TetrominoType::J: typeStr = "J"; break;
            case TetrominoType::L: typeStr = "L"; break;
        }
        rapidjson::Value& tetrominoDoc = document[typeStr];
        rapidjson::Value& colorDoc = tetrominoDoc["color"];
        int r = colorDoc["r"].GetInt();
        int g = colorDoc["g"].GetInt();
        int b = colorDoc["b"].GetInt();

        Color3B color = Color3B(r, g, b);
        
        std::vector<std::vector<Coordinate>> rotations;
        rapidjson::Value& rotationsDoc = tetrominoDoc["rotations"];
        
        for (rapidjson::SizeType rotationIndex = 0; rotationIndex < rotationsDoc.Size(); ++rotationIndex) {
            std::vector<Coordinate> singleRotate;
            for (rapidjson::SizeType cordinateIndex = 0; cordinateIndex < rotationsDoc[rotationIndex].Size(); ++cordinateIndex) {
                int x = rotationsDoc[rotationIndex][cordinateIndex]["x"].GetInt();
                int y = rotationsDoc[rotationIndex][cordinateIndex]["y"].GetInt();
                Coordinate coordinate = Coordinate(x, y);
                singleRotate.push_back(coordinate);
            }
            rotations.push_back(singleRotate);
        }
        
        TetrominoState tetrominoState;
        tetrominoState.rotations = rotations;
        tetrominoState.color = color;
    
        return tetrominoState;
    }
}