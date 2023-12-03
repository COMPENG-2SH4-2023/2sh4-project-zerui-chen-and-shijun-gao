#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include <iostream>
class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state
    Player(GameMechs *thisGMRef);
    ~Player();

    objPosArrayList *getPlayerPos(); // Upgrade this in iteration 3.
    void updatePlayerDir();
    void movePlayer();
    bool checkCollisionWithFood();
    bool checkCollisionWithSelf();
    Dir getMyDir();
    bool getLocalExitFlag();

    char convertDirEnumToChar(Player::Dir direction);

    // Dir convertDirEnumToChar(Dir myDir);
    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;

private:
    // objPos playerPos;   // Upgrade this in iteration 3.
    objPosArrayList *p_objPosArrayList;
    enum Dir myDir;
    bool localExitFlag;
};

#endif