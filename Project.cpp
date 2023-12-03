#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "objPosArrayList.h"
#include <iostream>

using namespace std;

#define DELAY_CONST 100000
// Global variables
bool exitFlag;
Player *pPlayer = NULL;
GameMechs *pGameMechs;
// Function declarations
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (exitFlag == false)
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false;
    // Initialize the exit flag to false
    pGameMechs = new GameMechs(15, 30);// Create a GameMechs instance with a board size of 15x30
    pPlayer = new Player(pGameMechs);// Create a player and associate it with the game mechanics
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
        pPlayer->updatePlayerDir();// Update the player's direction based on user input
        exitFlag = pPlayer->getLocalExitFlag();// Update the exit flag based on player's input
    }
}

void RunLogic(void)
{
    // Check if the game is still running
    if (pGameMechs->getExitFlagStatus() != true)
    {
    // Get player and food positions
        objPos playerPos;
        objPosArrayList *pobjPosArrayList = pPlayer->getPlayerPos();

        objPos foodPos;
        // Check for collision with food and update game state accordingly
        pPlayer->mainGameMechsRef->getFoodPos(foodPos);
        if (foodPos.symbol == 0)
        {
            pPlayer->mainGameMechsRef->generateFood(playerPos);
            pPlayer->mainGameMechsRef->getFoodPos(foodPos);
        }

        if (pPlayer->checkCollisionWithFood() == true)
        {
            pPlayer->movePlayer();
            pPlayer->mainGameMechsRef->generateFood(playerPos);
            pPlayer->mainGameMechsRef->getFoodPos(foodPos);
            pPlayer->mainGameMechsRef->incrementScore();
        }
        else
        {
            pPlayer->movePlayer();
        }
    }
}

void DrawScreen(void)
{

    MacUILib_clearScreen();
    int boardX = pPlayer->mainGameMechsRef->getBoardSizeX();
    int boardY = pPlayer->mainGameMechsRef->getBoardSizeY();
    // Get player and food positions
    objPos playerPos;
    objPosArrayList *pobjPosArrayList = pPlayer->getPlayerPos();

    objPos foodPos;
    pPlayer->mainGameMechsRef->getFoodPos(foodPos);
    // Iterate through each cell of the board and draw the game elements
    for (int i = 0; i < boardX; i++)
    {
        for (int j = 0; j < boardY; j++)
        {
            // Draw the boundaries of the game board
            if (i == 0 || i == boardX - 1 || j == 0 || j == boardY - 1)
            {
                cout << "#";
            }

            else
            {
                bool isPlayerSymbol = false;
                bool isfoodSymbol = false;
                int snakeSize = pobjPosArrayList->getSize();
                // Check if the current cell corresponds to the player's position
                for (int k = 0; k < snakeSize; k++)
                {
                    objPos playerPos;
                    pobjPosArrayList->getElement(playerPos, k);
                    if (i == playerPos.x && j == playerPos.y)
                    {
                        cout << playerPos.symbol;
                        isPlayerSymbol = true;
                        break;
                    }
                }
                if (i == foodPos.x && j == foodPos.y)
                {
                    cout << foodPos.symbol;
                    isfoodSymbol = true;
                }
                if (isPlayerSymbol == false && isfoodSymbol == false)
                {
                    cout << " ";
                }
            }
        }
        cout << endl;
    }

    if (pPlayer->checkCollisionWithSelf())
    {

        cout << "You died" << endl;
    }
    else
    {
        cout << "You score:";
        cout << pPlayer->mainGameMechsRef->getScore() << endl;
        cout << "========= DEBUG MESSAGE ========" << endl;
        cout << "Board Size:";
        cout << boardX;
        cout << "X";
        cout << boardY << endl;
        cout << "Direction:";
        cout << pPlayer->convertDirEnumToChar(pPlayer->getMyDir()) << endl;
        objPosArrayList *pobjPosArrayList = pPlayer->getPlayerPos();
        objPos playerHeadPos;
        pobjPosArrayList->getHeadElement(playerHeadPos);

        cout << "Snake Head: " << playerHeadPos.y << ", " << playerHeadPos.x << std::endl;
        
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    MacUILib_uninit();
}
