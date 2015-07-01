//
//  SceneManager.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__

class SceneManager
{
public:
    static SceneManager* getInstance();
    void enterGameScene(bool networked);
    void backToLobby();
private:
    SceneManager();
    ~SceneManager();
    
};


#endif /* defined(__Tetrominos__SceneManager__) */
