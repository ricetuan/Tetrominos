//
//  SceneManager.h
//  Tetrominos
//
//  Created by Liang Fan on 7/2/15.
//
//

#ifndef __Tetrominos__SceneManager__
#define __Tetrominos__SceneManager__
#include "NetworkingWrapper.h";

class SceneManager : NetworkingDelegate
{
public:
    static SceneManager* getInstance();
    void enterGameScene(bool networked);
    void backToLobby();
    
    void showPeerList();
    void receiveMultiplayerInvitations();
private:
    std::unique_ptr<NetworkingWrapper> networkingWrapper;
    
    SceneManager();
    ~SceneManager();
    
    void receivedData(const void* state, unsigned long length);
    void stateChanged(ConnectionState state);
};


#endif /* defined(__Tetrominos__SceneManager__) */
