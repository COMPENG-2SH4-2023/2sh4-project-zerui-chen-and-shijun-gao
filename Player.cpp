#include "Player.h"
#include "objPos.h"
#include <iostream>

Player::Player(GameMechs *thisGMRef) : localExitFlag(false)
{
    // Initialize the Player object with the given GameMechs reference

    // Set the mainGameMechsRef to the provided GameMechs reference
    // This establishes a connection between the Player and the game mechanics.

    // Initialize the player's direction to STOP
    mainGameMechsRef = thisGMRef;// Create a new objPosArrayList to store the player's positions
    myDir = STOP;
    p_objPosArrayList = new objPosArrayList();
    objPos playerPos;
    playerPos.x = 5;
    playerPos.y = 10;
    playerPos.symbol = '*';
    p_objPosArrayList->insertTail(playerPos);
    // Insert the initial position into the ArrayList

}

Player::~Player()
{
    // delete any heap members here
}

objPosArrayList *Player::getPlayerPos()
{

    return p_objPosArrayList;
}

Player::Dir Player::getMyDir()
{
    return myDir;
}

char Player::convertDirEnumToChar(Player::Dir direction)
{
    switch (direction)
    {
    case UP:
        return 'U';
    case DOWN:
        return 'D';
    case LEFT:
        return 'L';
    case RIGHT:
        return 'R';
    case STOP:
        return 'S';
    default:
        return ' '; 
    }
}


void Player::updatePlayerDir()
{
    // // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();

    if (input != 0)
    {
        switch (input)
        {
        case ' ':
            mainGameMechsRef->setExitTrue();
            localExitFlag = mainGameMechsRef->getExitFlagStatus();

            return;

        case 's':
            if (myDir == UP)
            {
                myDir = UP;
            }
            else
            {
                myDir = DOWN;
            }
            break;

        case 'w':
            if (myDir == DOWN)
            {
                myDir = DOWN;
            }
            else
            {
                myDir = UP;
            }
            break;

        case 'a':
            if (myDir == RIGHT)
            {
                myDir = RIGHT;
            }
            else
            {
                myDir = LEFT;
            }
            break;

        case 'd':
            if (myDir == LEFT)
            {
                myDir = LEFT;
            }
            else
            {
                myDir = RIGHT;
            }
            break;

        default:
            break;
        }
        mainGameMechsRef->setInput(0);

    }
}

bool Player::checkCollisionWithFood()
{
    objPosArrayList *pobjPosArrayList = getPlayerPos();
    // Retrieve the player's position ArrayList
    objPos playerHeadPos;
    pobjPosArrayList->getHeadElement(playerHeadPos);

    objPos foodPos;
    mainGameMechsRef->getFoodPos(foodPos);

    // Check for overlap with snakehead position
    if (playerHeadPos.isPosEqual(&foodPos))
    {
        return true; // collision 
    }

    return false; // no collision 
}

bool Player::checkCollisionWithSelf()
{
    objPosArrayList *pobjPosArrayList = getPlayerPos();
    objPos playerHeadPos;
    pobjPosArrayList->getElement(playerHeadPos, 0);

    // Iterate over the snake's body, checking to see if it overlaps with the snake's head.
    for (int i = 1; i < pobjPosArrayList->getSize(); ++i)
    {
        objPos bodyPos;
        pobjPosArrayList->getElement(bodyPos, i);
        if (playerHeadPos.isPosEqual(&bodyPos))
        {
            // Collision
            return true;
        }
    }

    // No collision
    return false;
}

void Player::movePlayer()
{

    objPosArrayList *pobjPosArrayList = getPlayerPos();
    objPos playerHeadPos;
    pobjPosArrayList->getElement(playerHeadPos, 0);
    // PPA3 Finite State Machine logic

    if (checkCollisionWithSelf())
    {
     // Collision occurs, set game exit flag and fail flag
        mainGameMechsRef->setLoseFlag();
        localExitFlag = mainGameMechsRef->getExitFlagStatus();

        
        return; // Exit the function without performing the following move logic
    }
    switch (myDir)
    {
    case STOP:
    // Do not perform any action
        break;

    case DOWN:
        playerHeadPos.x++;
        if (playerHeadPos.x > 13)
        {
            playerHeadPos.x = 1;
        }
        break;

    case UP:
        playerHeadPos.x--;
        if (playerHeadPos.x < 1)
        {
            playerHeadPos.x = 13;
        }
        break;

    case LEFT:
        playerHeadPos.y--;
        if (playerHeadPos.y < 1)
        {
            playerHeadPos.y = 28;
        }
        break;

    case RIGHT:
        playerHeadPos.y++;
        if (playerHeadPos.y > 28)
        {
            playerHeadPos.y = 1;
        }
        break;

    default:
        break;
    }

    objPos currentPlayerPos(playerHeadPos);
    if (!checkCollisionWithFood())
    {
        p_objPosArrayList->insertHead(currentPlayerPos);
        p_objPosArrayList->removeTail();
    }
    else
    {
        // Collisions occur, increasing the length of the snake and generating new food.

        p_objPosArrayList->insertHead(currentPlayerPos);
    }
}

bool Player::getLocalExitFlag()
{
    return localExitFlag;
}