#include "GameMechs.h"
#include "MacUILib.h"
GameMechs::GameMechs()
{
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY;
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

char GameMechs::getInput()
{
    input = MacUILib_getChar();
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = ' ';
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}
int GameMechs::getScore()
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

void GameMechs::getFoodPos(objPos &returnPos)
{
    returnPos = foodPos;
}

void GameMechs::generateFood(objPos blockOff)
{
    srand((unsigned int)time(NULL));// Seed the random number generator
    int accept = 1;// Variable to control whether the generated food position is accepted
    while (accept == 1)// Continue generating a new position until it is accepted
    {
        // Generate random coordinates within the game board (excluding borders)
        int xx = rand() % (boardSizeX - 2) + 1;
        int yy = rand() % (boardSizeY - 2) + 1;
        char showsymbol = '0';
        accept = 0;
        // Check if the generated position is the same as the blockOff position
        if (blockOff.y == xx && blockOff.x == yy)
        {
            accept = 1;
        }
        else
        {
            // If not, set the foodPos with the generated position and symbol
            foodPos.x = xx;
            foodPos.y = yy;
            foodPos.symbol = showsymbol;
        }
    }
}