#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "objPos.h"

objPos::objPos()
{
    x = 0;
    y = 0;
    symbol = 0; // NULL
}

objPos::objPos(objPos &o)
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

objPos::objPos(int xPos, int yPos, char sym)
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::setObjPos(objPos o)
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

void objPos::getObjPos(objPos &returnPos)
{
    returnPos.setObjPos(x, y, symbol);
}

char objPos::getSymbol()
{
    return symbol;
}

bool objPos::isPosEqual(const objPos *refPos)
{
    return (refPos->x == x && refPos->y == y);
}

char objPos::getSymbolIfPosEqual(const objPos *refPos)
{
    if (isPosEqual(refPos))
        return getSymbol();
    else
        return 0;
}

bool objPos::isOnEdge(int maxRows, int maxCols)
{
    if (x == 0 || x == maxRows - 1 || y == 0 || y == maxCols - 1)
    {
        symbol = '#'; // If on the edge, change symbol to '#'.
        return true;
    }
    return false;
}
